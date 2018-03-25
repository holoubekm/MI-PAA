#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <fstream>
#include <math.h>
#include <omp.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <limits>
#include <sstream>

using namespace std;
#define DEBUG

struct item {
  int cost;
  int weight;
  int normalizedCost;
  bool state;
};
item* items;

int** dynArray;

int tmp_max;
int noItems;
int capacity;
int totalCost;

/* Bruteforce solution */
void rekDumb(int i, int fr_cap, int price) {
  if (i == noItems) {
    if ((price > tmp_max) && (fr_cap >= 0)) {
      tmp_max = price;
    }
    return;
  }
  rekDumb(i+1, fr_cap, price);
  rekDumb(i+1, fr_cap - items[i].weight, price + items[i].cost);
}



/* Naive heuristic */
void rekRatio(int i, int fr_cap, int price) {
  if (i == noItems) {
    if ((price > tmp_max) && (fr_cap >= 0)) {
      tmp_max = price;
    }
    return;
  }

  if(fr_cap >= items[i].weight) {
    rekRatio(i+1, fr_cap - items[i].weight, price + items[i].cost);
  } else {
    rekRatio(i+1, fr_cap, price);
  }
}



/* Branch and bounds solution */
float maxBenefit(int i, int fr_cap, int price) {
  float maxBenefit = 0;
  while(i < noItems) {
    if(items[i].weight <= fr_cap) {
      fr_cap -= items[i].weight;
      maxBenefit += items[i].cost;
    } else {
      maxBenefit += items[i].cost * (fr_cap / (float)items[i].weight);
      break;
    }
    i++;
  }
  return maxBenefit + price;
}

void rekBB(int i, int fr_cap, int price) {
  if (price > tmp_max && fr_cap >= 0) {
    tmp_max = price;
  }

  if(i == noItems)
    return;

  auto benefit = maxBenefit(i + 1, fr_cap - items[i].weight, price + items[i].cost);
  if(fr_cap - items[i].weight >= 0 && benefit > tmp_max) {
    rekBB(i + 1, fr_cap - items[i].weight, price + items[i].cost);
  }

  benefit = maxBenefit(i + 1, fr_cap, price);
  if(benefit > tmp_max) {
    rekBB(i + 1, fr_cap, price);
  }
}


/* Dynamic decomposition */
void rekDyn_(int i, int fr_cap, int p, int w) {

  if(w >= dynArray[i][p] || w > fr_cap)
  	return;
  dynArray[i][p] = w;
  
  if(i >= noItems)
    return;

  rekDyn_(i + 1, fr_cap, p + items[i].cost, dynArray[i][p] + items[i].weight);
  rekDyn_(i + 1, fr_cap, p, dynArray[i][p]);
}

void rekDyn(int i, int fr_cap, int p, int w) {
	totalCost = 0;
    for(int x = 0; x < noItems; x++)
      totalCost += items[x].cost;

    dynArray = new int*[noItems + 1];
    for(int x = 0; x < noItems + 1; x++) {
      dynArray[x] = new int[totalCost + 1];
      for(int y = 0; y < totalCost + 1; y++) {
      	dynArray[x][y] = INT_MAX / 2;
      }
    }
    dynArray[0][0] = 0;

	rekDyn_(1, fr_cap, 0, 0);
	rekDyn_(1, fr_cap, items[0].cost, items[0].weight);


	// for(int x = 0; x <= noItems; x++) {
	// 	for(int y = 0; y <= totalCost; y++) {
	// 		auto val = dynArray[x][y];
	// 		if(val == INT_MAX / 2)
	// 			val = -1;
	// 		cout << val << " ";
	// 	} cout << endl;
	// } cout << endl;

	for(int x = totalCost; x >= 0; x--) {
		auto val = dynArray[noItems][x];
		if(val != INT_MAX / 2) {
			tmp_max = x;
			break;
		}
	}

	for(int x = 0; x < noItems + 1; x++) {
      delete[] dynArray[x];
    }
    delete[] dynArray;
}



/* FPTAS decomposition */
void rekFPTAS_(int i, int fr_cap, int p, int w) {

  if(w >= dynArray[i][p] || w > fr_cap)
  	return;
  dynArray[i][p] = w;
  
  if(i >= noItems)
    return;

  rekFPTAS_(i + 1, fr_cap, p + items[i].normalizedCost, dynArray[i][p] + items[i].weight);
  rekFPTAS_(i + 1, fr_cap, p, dynArray[i][p]);
}

void rekFPTAS(int i, int fr_cap, int p, int w, double eps) {
	auto maxCost = 0;
	for(int x = 0; x < noItems; x++) {
		if(maxCost < items[x].cost) {
			maxCost = items[x].cost;
		}
    }

    auto avgEpsCost = (eps * maxCost) / noItems;
    for(int x = 0;x < noItems; x++) {
    	items[x].normalizedCost = static_cast<int>(items[x].cost / avgEpsCost);
    }

    totalCost = 0;
    for(int x = 0; x < noItems; x++)
      totalCost += items[x].normalizedCost;

    dynArray = new int*[noItems + 1];
    for(int x = 0; x < noItems + 1; x++) {
      dynArray[x] = new int[totalCost + 1];
      for(int y = 0; y < totalCost + 1; y++) {
      	dynArray[x][y] = INT_MAX / 2;
      }
    }
    dynArray[0][0] = 0;

	rekFPTAS_(1, fr_cap, 0, 0);
	rekFPTAS_(1, fr_cap, items[0].normalizedCost, items[0].weight);


	// for(int x = 0; x <= noItems; x++) {
	// 	for(int y = 0; y <= totalCost; y++) {
	// 		auto val = dynArray[x][y];
	// 		if(val == INT_MAX / 2)
	// 			val = -1;
	// 		cout << val << " ";
	// 	} cout << endl;
	// } cout << endl;

	for(int x = totalCost; x >= 0; x--) {
		auto val = dynArray[noItems][x];
		if(val != INT_MAX / 2) {
			tmp_max = x * avgEpsCost;
			break;
		}
	}

	for(int x = 0; x < noItems + 1; x++) {
      delete[] dynArray[x];
    }
    delete[] dynArray;
}



int cmp(const void* a,const void* b) {
  item* ia = (item*)a;
  item* ib = (item*)b;
  return (ia->cost / (float)ia->weight) < (ib->cost / (float)ib->weight);
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    cerr << "Not enough arguments" << endl;
    return 1;
  }

  ifstream inst(argv[1]);

  istringstream is(argv[2]);
  double eps = 0;
  is >> eps;
  eps /= 100;

  cout << eps << endl;
  if(!inst.good()) {
    cerr << "Cannot open input file: " << argv[1] << endl;
    return 2;
  }

  double maxErr = 0;
  double totalErr = 0;
  double totalTimeBB = 0;
  double totalTimeDyn = 0;
  double totalTimeFPTAS = 0;

  int repeat = 10;
  int count = 50;
  cout << fixed;

#ifndef DEBUG
  cout << "[";
#endif

  for(int i = 0; i < count; i++ ) { 
  #ifndef DEBUG
    cout << "-";
    cout << flush;
  #endif

    int id = 0;

    inst >> id >> noItems >> capacity;
    items = new item[noItems];

  #ifdef DEBUG
    cout << "cap: " << capacity << ", items: " << noItems << endl;
  #endif

    for(int x = 0; x < noItems; x++) {
      inst >> items[x].weight >> items[x].cost;
      items[x].state = false;
      items[x].normalizedCost = 0.0;
      // cout << "w: " << items[x].weight << ", c: " << items[x].cost << endl;
    }

    double start, end;
    qsort(items, noItems, sizeof(item), cmp);

    start = omp_get_wtime();
    tmp_max = -1;
    // rekBB(0, capacity, 0);
    double cBB = tmp_max;
    end = omp_get_wtime();
    double time = end - start;
    totalTimeBB += time;
  #ifdef DEBUG
    cout << "BB: " << endl;
    cout << "\tmaximum: " << cBB << endl;
    cout << "\ttime: " << time << endl;
  #endif

    start = omp_get_wtime();
    tmp_max = -1;
    for(long aaa = 0; aaa < repeat; aaa++) {
	    rekDyn(0, capacity, 0, 0);
	}
    double cDyn = tmp_max;
    end = omp_get_wtime();
    time = end - start;
    time = time / repeat;
    totalTimeDyn += time;
  #ifdef DEBUG
    cout << "DYN: " << endl;
    cout << "\tmaximum: " << cDyn << endl;
    cout << "\ttime: " << time << endl;
  #endif

    start = omp_get_wtime();
    for(long aaa = 0; aaa < repeat; aaa++) {
      tmp_max = -1;
      rekFPTAS(1, capacity, 0, 0, eps);
    }
	double cFPTAS = tmp_max;
    end = omp_get_wtime();
    time = end - start;
    time = time / repeat;
    totalTimeFPTAS += time;
    double err = (cDyn - cFPTAS)/cDyn;
  #ifdef DEBUG
    cout << "FPTAS: " << endl;
    cout << "\tmaximum: " << cFPTAS << endl;
    cout << "\ttime: " << time << endl;
    cout << "\te: " << err << endl << endl;
  #endif

    if(err > maxErr)
      maxErr = err;
    totalErr += err;
    delete[] items;
  }

#ifndef DEBUG
  cout << "]" << endl;
#endif

  cout << "input: " << argv[1] << endl;
  cout << "eps: " << eps << endl;
  cout << "max_err: " << maxErr << endl;
  cout << "avg_err: " << (totalErr / count) << endl;
  cout << "avg_time_bb: " << (totalTimeBB / count) << endl;
  cout << "avg_time_dyn: " << (totalTimeDyn / count) << endl;
  cout << "avg_time_fptas: " << (totalTimeFPTAS / count) << endl;
  cout << "total_time_bb: " << totalTimeBB << endl;
  cout << "total_time_fptas: " << totalTimeFPTAS << endl;
  cout << "total_time_dyn: " << totalTimeDyn << endl << endl;
  inst.close();
  return 0;
}

