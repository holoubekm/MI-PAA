#include "stdafx.h"
#include "instance.h"
#include "sat3.h"
#include "clause.h"

Instance::Instance(SAT3* pInstance, int pVarCount) :
		mSAT(pInstance),
		mVarCount(pVarCount),
		mValue(0), 
		mIsFeasible(false) {

	mItems = new bool[mVarCount + 1];
	for (int x = 0; x < mVarCount + 1; x++) {
		mItems[x] = false;
	}
}

void Instance::Compute() {
	auto clauses = mSAT->mClauses;
	auto clausesCount = mSAT->mClausesCount;

	mIsFeasible = true;
	mValue = 0;

	for (auto x = 0; x < clausesCount; x++) {
		if(!clauses[x]->Evaluate(this)) { 
			mIsFeasible = false;
		} 
	}

	for(auto x = 0; x < mVarCount; x++) {
		mValue += (mItems[x] ? mSAT->mWeights[x] : 0);
	}

	//if (mWeight > mInstance->mCap) {
	//	throw new exception();
	//}
}

Instance* Instance::Clone() {
	auto ret = new Instance(mSAT, mVarCount);
	for (int x = 1; x <= mVarCount; x++) {
		ret->mItems[x] = mItems[x];
	}
	ret->mIsFeasible = mIsFeasible;
	ret->mValue = mValue;
	return ret;
}
Instance* Instance::Mutate(double pFactor) {
	
	auto gen = new Instance(mSAT, mVarCount);
	for (int x = 1; x <= mVarCount; x++) {
		gen->mItems[x] = mItems[x];
	}

	bool mutate = mSAT->mRealDis(mSAT->mGn) <= pFactor;
	if(mutate) {
		auto index = mSAT->mDis(mSAT->mGn);
		// cout << "Mutuju " << index << endl;
		gen->mItems[index] = !gen->mItems[index];
	}

	// auto count = (int)(pFactor * (mVarCount + 1));
	// for (int x = 1; x < count; x++) {
	// 	auto index = mSAT->mDis(mSAT->mGn);
	// 	gen->mItems[index] = !gen->mItems[index];
	// }
	
	gen->Compute();
	return gen;
}

Instance* Instance::CrossInstances(Instance* pRhs) {
	auto gen = new Instance(mSAT, mVarCount);
	auto index = mSAT->mDis(mSAT->mGn);
	for (int inx = 1; inx < index; inx++) {
		gen->mItems[inx] = mItems[inx];
	}
	for (int inx = index; inx <= mVarCount; inx++) {
		gen->mItems[inx] = pRhs->mItems[inx];
	}
	gen->Compute();

#ifdef _DEBUG
#endif
	return gen;
}

Instance::~Instance()
{
	delete[] mItems;
}

bool Instance::Comparator(const Instance* pLhs, const Instance* pRhs) {
	if (pLhs->mIsFeasible < pRhs->mIsFeasible)
		return true;
	if (pLhs->mIsFeasible > pRhs->mIsFeasible)
		return false;
	return pLhs->mValue < pRhs->mValue;
}