#include "stdafx.h"
#include "instance.h"
#include "item.h"
#include "knapsack.h"

Instance::Instance(Knapsack* pInstance, int pItemsCount) : 
		mInstance(pInstance), 
		mItemsCount(pItemsCount), 
		mWeight(0),
		mPrice(0) {

	mItems = new bool[pItemsCount];
	for (int x = 0; x < pItemsCount; x++) {
		mItems[x] = false;
	}
}

void Instance::Compute() {
	mWeight = 0.0;
	mPrice = 0.0;
	for (int x = 0; x < mItemsCount; x++) {
		if (mItems[x]) {
			mWeight += mInstance->mItems[x]->mWeight;
			mPrice += mInstance->mItems[x]->mPrice;
		}
	}

	if (mWeight > mInstance->mCap) {
		throw new exception();
	}
}

Instance* Instance::Clone() {
	auto ret = new Instance(mInstance, mItemsCount);
	for (int x = 0; x < mItemsCount; x++) {
		ret->mItems[x] = mItems[x];
	}
	ret->mWeight = mWeight;
	ret->mPrice = mPrice;
	return ret;
}
Instance* Instance::Mutate(double pFactor) {
	
	auto gen = new Instance(mInstance, mItemsCount);
	for (int x = 0; x < mItemsCount; x++) {
		gen->mItems[x] = mItems[x];
	}
	gen->mWeight = mWeight;
	gen->mPrice = mPrice;

	auto count = (int)(pFactor * mItemsCount);
	for (int x = 0; x < count; x++) {
		auto index = mInstance->mDis(mInstance->mGn);

		if (!gen->mItems[index] && gen->mWeight + mInstance->mItems[index]->mWeight < mInstance->mCap) {
			gen->mItems[index] = true;
			gen->mWeight += mInstance->mItems[index]->mWeight;
			gen->mPrice += mInstance->mItems[index]->mPrice;
		}
		else if(gen->mItems[index]) {
			gen->mItems[index] = false;
			gen->mWeight -= mInstance->mItems[index]->mWeight;
			gen->mPrice -= mInstance->mItems[index]->mPrice;
		}
	}

#ifdef _DEBUG
	auto tmpWeight = gen->mWeight;
	auto tmpPrice = gen->mPrice;
	gen->Compute();
	if (tmpWeight != gen->mWeight || tmpPrice != gen->mPrice) {
		throw new exception();
	}
#endif

	return gen;
}

Instance::~Instance()
{
	delete[] mItems;
}

bool Instance::Comparator(const Instance* pLhs, const Instance* pRhs) {
	if (pLhs->mPrice < pRhs->mPrice)
		return true;
	if (pLhs->mPrice > pRhs->mPrice)
		return false;
	if (pLhs->mWeight > pRhs->mWeight)
		return true;
	if (pLhs->mWeight < pRhs->mWeight)
		return false;
	return false;
}