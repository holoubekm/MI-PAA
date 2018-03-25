#include "stdafx.h"
#include "sat3.h"
#include "item.h"
#include "instance.h"
#include "clause.h"

SAT3::SAT3(int pClausesCount, int pVarCount) : 
	mClausesCount(pClausesCount), mVarCount(pVarCount),
	mRd(), mGn(mRd()), mDis(1, mVarCount), mRealDis(0, 1) {
	mClauses = new Clause*[mClausesCount];

	std::random_device rd;
	std::mt19937 gen(rd());
	mWeights = new int[mVarCount];
	uniform_int_distribution<> dis(1, 50);

	for(auto x = 0; x < mVarCount; x++) {
		mWeights[x] = dis(gen);
	}
}

SAT3::~SAT3() {
	for (int x = 0; x < mClausesCount; x++) {
		delete mClauses[x];
	}
	delete[] mClauses;
	delete[] mWeights;
}

Instance* SAT3::GetRandomGeneration() {
	auto gen = new Instance(this, mVarCount);
	for (int x = 0; x < 2 * mVarCount; x++) {
		auto index = mDis(mGn);
		gen->mItems[index] = !gen->mItems[index];
	}

	gen->Compute();
#ifdef _DEBUG

#endif
	return gen;
}