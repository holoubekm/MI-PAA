#ifndef __KNAPSACK__
#define __KNAPSACK__

#include <vector>

using namespace std;

class Item;
class Instance;

class Knapsack {
public:
	Knapsack(int pCap, int pItemsCount);
	~Knapsack();
	Instance* GetRandomGeneration();
	Instance* CrossInstances(Instance* pLhs, Instance* pRhs);

public:
	int mCap;
	Item** mItems;
	int mItemsCount;

	random_device mRd;
	mt19937 mGn;
	uniform_int_distribution<> mDis;
};

#endif
