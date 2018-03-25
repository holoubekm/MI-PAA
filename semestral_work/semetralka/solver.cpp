#include "stdafx.h"
#include "solver.h"
#include "sat3.h"
#include "instance.h"
#include "item.h"
#include "clause.h"

Solver::Solver(int pClausesCount, int pVarCount) :
	mSAT(new SAT3(pClausesCount, pVarCount)),
	mClausesCount(pClausesCount),
	mClausesAdded(0),
	mVarCount(pVarCount),
	mInstances(200),
	mIterations(750),
	mKeepBest(25),
	mKeepWorst(15),
	mCross(75),
	mMutationFactor(0.05),
	mBestSolution(0.0),
	mStartTime(0.0),
	mEndTime(0.0),
	mFirstFeasibleIter(0) {
}

void Solver::AddClause(int pA, int pB, int pC) {
	mSAT->mClauses[mClausesAdded] = new Clause(pA, pB, pC);
#ifdef _DEBUG
	if (mSAT->mClauses[mClausesAdded]->mInxA <= 0 || mSAT->mClauses[mClausesAdded]->mInxA > mVarCount ||
		mSAT->mClauses[mClausesAdded]->mInxB <= 0 || mSAT->mClauses[mClausesAdded]->mInxB > mVarCount ||
		mSAT->mClauses[mClausesAdded]->mInxC <= 0 || mSAT->mClauses[mClausesAdded]->mInxC > mVarCount ) {
		throw new exception();
	}
#endif
	mClausesAdded++;
}

int Solver::GetBiasedIndex(mt19937& pGen, geometric_distribution<>& pExpDis) {
	auto val = pExpDis(pGen);
	while(val >= (mInstances - 1))
		val = pExpDis(pGen);

	val = mInstances - val - 1;
	// cout << val << endl;
	return val;
}

void Solver::Start() {
	mStartTime = GetCPUTime();
	random_device rd;
	mt19937 gn(rd());
	uniform_int_distribution<> dis(0, mInstances - 1);
    geometric_distribution<> expdis(0.1);

	auto gen = new Instance*[mInstances];
	for (int x = 0; x < mInstances; x++) {
		gen[x] = mSAT->GetRandomGeneration();
	}

	mFirstFeasibleIter = 0;
	for (int iter = 0; iter < mIterations; iter++) {
		sort(gen, gen + mInstances, Instance::Comparator);
		if (gen[mInstances - 1]->mValue > mBestSolution && gen[mInstances - 1]->mIsFeasible) {
			if(mFirstFeasibleIter == 0) {
				mFirstFeasibleIter = iter;
			}

			mBestSolution = gen[mInstances - 1]->mValue;
		}

		if (iter % 10 == 0) {

			auto totalValue = 0;
			for (int x = 0; x < mInstances; x++) {
				totalValue += gen[x]->mValue;
			}

			auto bestFeasible = gen[mInstances - 1]->mIsFeasible ? gen[mInstances - 1]->mValue : 0;
			cout << "Gen: " << (iter + 0) << ", BestSol: " << gen[mInstances - 1]->mValue << ", BestFeasibleSol: " << bestFeasible << ", GenAvgValue: " << ((double)totalValue / mInstances) << endl;
			

			// for(int x = mInstances - 1; x >= 0; x--) {
				// cout << "\tSol: " << gen[x]->mValue << endl;
			// }
			//auto eps = 100 * (pOptimalSolution - gen[mInstances - 1]->mPrice) / pOptimalSolution;
			//cout << "GenError: " << eps << endl << endl;
		}

		auto newgen = new Instance*[mInstances];
		auto inx = 0;
		for (int x = 0; x < mKeepBest; x++, inx++) {
			// cout << "Clone" << endl;
			newgen[inx] = gen[mInstances - x - 1]->Clone();
		}

		for (int x = 0; x < mKeepWorst; x++, inx++) {
			newgen[inx] = gen[x]->Clone();
		}

		for (int x = 0; x < mCross; x++, inx++) {
			// cout << "Cross" << endl;
			auto mother = GetBiasedIndex(gn, expdis);
			auto father = GetBiasedIndex(gn, expdis);
			while (mother == father)
				father = GetBiasedIndex(gn, expdis);

			newgen[inx] = gen[mother]->CrossInstances(gen[father]);
		}
		for (; inx < mInstances; inx++) {
			// cout << "Mutate" << endl;
			// auto parent = dis(gn);
			auto parent = GetBiasedIndex(gn, expdis);
			// cout << gen[parent]->mValue << endl;
			newgen[inx] = gen[parent]->Mutate(mMutationFactor);
			// cout << newgen[inx]->mValue << endl << endl;
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

int Solver::GetFirstFeasibleIter() {
	return mFirstFeasibleIter;
}

Solver::~Solver() {
	delete mSAT;
}
