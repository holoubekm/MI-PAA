#ifndef __SAT3__
#define __SAT3__

#include <vector>

using namespace std;

class Clause;
class Instance;

class SAT3 {
public:
	//SAT3(int pCap, int pItemsCount);
	SAT3(int pClausesCount, int pVarCount);
	~SAT3();
	Instance* GetRandomGeneration();

public:
	Clause** mClauses;
	int* mWeights;
	
	int mClausesCount;
	int mVarCount;

	//int mCap;
	//Item** mItems;
	//int mItemsCount;

	random_device mRd;
	mt19937 mGn;
	uniform_int_distribution<> mDis;
	uniform_real_distribution<> mRealDis;
};

#endif
