#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <fstream>
#include <math.h>
#include <omp.h>
#include <algorithm>
#include <iostream>

using namespace std;

struct item {
  int cost;
  int weight;
  bool state;
};
item* items;

int tmp_max;
int noItems;
int capacity;

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

int cmp(const void* a,const void* b) {
  item* ia = (item*)a;
  item* ib = (item*)b;
  return (ia->cost / (float)ia->weight) < (ib->cost / (float)ib->weight);
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    cerr << "Not enough arguments" << endl;
    return 1;
  }

  ifstream inst(argv[1]);

  if(!inst.good()) {
    cerr << "Cannot open input file: " << argv[1] << endl;
    return 2;
  }

  double maxErr = 0;
  double totalErr = 0;
  double totalTimeOpt = 0;
  double totalTimeApx = 0;

  int count = 50;

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
      // cout << "w: " << items[x].weight << ", c: " << items[x].cost << endl;
    }

    double cOpt, cApx;
    double start, end;

    start = omp_get_wtime();
    tmp_max = -1;
    rekDumb(0, capacity, 0);
    cOpt = tmp_max;
    end = omp_get_wtime();
    double time = end - start;
    totalTimeOpt += time;
  #ifdef DEBUG
    cout << "maximum: " << cOpt << endl;
    cout << "time: " << time << endl;
  #endif

    start = omp_get_wtime();
    qsort(items, noItems, sizeof(item), cmp);
    for(long aaa = 0; aaa < 1000000; aaa++) {
      tmp_max = -1;
      rekRatio(0, capacity, 0);
    }
    cApx = tmp_max;
    end = omp_get_wtime();
    time = end - start;
    totalTimeApx += time;
    double err = (cOpt - cApx)/cOpt;
  #ifdef DEBUG
    cout << "maximum: " << cApx << endl;
    cout << "time: " << time << endl;
    cout << "e: " << err << endl << endl;
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
  cout << "max_err: " << maxErr << endl;
  cout << "avg_err: " << (totalErr / count) << endl;
  cout << "avg_time_opt: " << (totalTimeOpt / count) << endl;
  cout << "avg_time_apx: " << (totalTimeApx / count) << endl;
  cout << "total_time_opt: " << totalTimeOpt << endl;
  cout << "total_time_apx: " << totalTimeApx << endl << endl;
  inst.close();
  return 0;
}

