#include "stdafx.h"
#include "solver.h"
#include "knapsack.h"
#include "instance.h"
#include "item.h"

Solver::Solver(int pCapacity, int pItemsCount) :
	mProblem(new Knapsack(pCapacity, pItemsCount)),
	mCapacity(pCapacity),
	mItemsCount(pItemsCount),
	mItemsAdded(0),
	mInstances(200),
	mIterations(750),
	mKeepBest(25),
	mKeepWorst(15),
	mCross(75),
	mMutationFactor(0.05),
	mBestSolution(0.0),
	mStartTime(0.0),
	mEndTime(0.0),
	mRelativeError(0.0) {
}

void Solver::AddItem(double mWeight, double mPrice) {
	mProblem->mItems[mItemsAdded++] = new Item(mWeight, mPrice);
}

void Solver::Start(double pOptimalSolution) {
	mStartTime = GetCPUTime();
	random_device rd;
	mt19937 gn(rd());
	uniform_int_distribution<> dis(0, mInstances - 1);

	auto gen = new Instance*[mInstances];
	for (int x = 0; x < mInstances; x++) {
		gen[x] = mProblem->GetRandomGeneration();
	}

	for (int iter = 0; iter < mIterations; iter++) {
		sort(gen, gen + mInstances, Instance::Comparator);
		if (gen[mInstances - 1]->mPrice > mBestSolution) {
			mBestSolution = gen[mInstances - 1]->mPrice;
		}

		if (iter % 99 == 0) {
			cout << "Gen: " << (iter + 0) << endl;
			cout << "BestSol: " << (gen[mInstances - 1]->mPrice) << endl;

			auto totalWeight = 0.0;
			auto totalPrice = 0.0;
			for (int x = 0; x < mInstances; x++) {
				totalWeight += gen[x]->mWeight;
				totalPrice += gen[x]->mPrice;
			}
			cout << "GenAvgPrice: " << (totalPrice / mInstances) << endl;
			cout << "GenAvgWeight: " << (totalWeight / mInstances) << endl;
			auto eps = 100 * (pOptimalSolution - gen[mInstances - 1]->mPrice) / pOptimalSolution;
			cout << "GenError: " << eps << endl << endl;
		}

		auto newgen = new Instance*[mInstances];
		auto inx = 0;
		for (int x = 0; x < mKeepBest; x++, inx++) {
			newgen[inx] = gen[mInstances - x - 1]->Clone();
		}

		for (int x = 0; x < mKeepWorst; x++, inx++) {
			newgen[inx] = gen[x]->Clone();
		}

		for (int x = 0; x < mCross; x++, inx++) {
			auto mother = dis(gn);
			auto father = dis(gn);
			while (mother == father)
				father = dis(gn);

			newgen[inx] = mProblem->CrossInstances(gen[mother], gen[father]);
		}
		for (; inx < mInstances; inx++) {
			newgen[inx] = gen[dis(gn)]->Mutate(mMutationFactor);
		}

		for (int x = 0; x < mInstances; x++) {
			delete gen[x];
		}
		delete[] gen;
		gen = newgen;
	}
	for (int x = 0; x < mInstances; x++)
		delete gen[x];
	delete[] gen;
	mEndTime = GetCPUTime();
}

double Solver::GetElapsedTime() {
	return mEndTime - mStartTime;
}

double Solver::GetBestSolution() {
	return mBestSolution;
}

Solver::~Solver() {
	delete mProblem;
}
