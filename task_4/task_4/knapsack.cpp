#include "stdafx.h"
#include "knapsack.h"
#include "item.h"
#include "instance.h"

Knapsack::Knapsack(int pCap, int pItemsCount) : mCap(pCap), mItemsCount(pItemsCount),
	mRd(), mGn(mRd()), mDis(0, mItemsCount - 1) {
	mItems = new Item*[mItemsCount];
}

Knapsack::~Knapsack() {
	for (int x = 0; x < mItemsCount; x++) {
		delete mItems[x];
	}
	delete[] mItems;
}

Instance* Knapsack::GetRandomGeneration() {
	auto gen = new Instance(this, mItemsCount);
	for (int x = 0; x < 2 * mItemsCount; x++) {
		auto index = mDis(mGn);

		if (!gen->mItems[index] && gen->mWeight + mItems[index]->mWeight <= mCap) {
			gen->mItems[index] = true;
			gen->mWeight += mItems[index]->mWeight;
			gen->mPrice += mItems[index]->mPrice;
		}
		else if(gen->mItems[index]) {
			gen->mItems[index] = false;
			gen->mWeight -= mItems[index]->mWeight;
			gen->mPrice -= mItems[index]->mPrice;
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

Instance* Knapsack::CrossInstances(Instance* pLhs, Instance* pRhs) {

	auto index = mDis(mGn);
	auto gen = new Instance(this, mItemsCount);
	for (int inx = 0; inx < index; inx++) {
		if (pLhs->mItems[inx] && gen->mWeight + mItems[inx]->mWeight <= mCap) {
			gen->mItems[inx] = true;
			gen->mWeight += mItems[inx]->mWeight;
			gen->mPrice += mItems[inx]->mPrice;
		}
	}
	for (int inx = index; inx < mItemsCount; inx++) {
		if (pRhs->mItems[inx] && gen->mWeight + mItems[inx]->mWeight <= mCap) {
			gen->mItems[inx] = true;
			gen->mWeight += mItems[inx]->mWeight;
			gen->mPrice += mItems[inx]->mPrice;
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