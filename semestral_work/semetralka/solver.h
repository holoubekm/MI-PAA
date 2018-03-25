#pragma once
#include <string>

using namespace std;

class SAT3;
class Solver
{
public:
	Solver(int pClausesCount, int pVarCount);
	void AddClause(int pA, int pB, int pC);

	void Start();
	double GetElapsedTime();
	double GetBestSolution();
	int GetFirstFeasibleIter();
	int GetBiasedIndex(mt19937& pGen, geometric_distribution<>& pExpDis);

	~Solver();

public:
	SAT3* mSAT;

	int mClausesCount;
	int mClausesAdded;
	int mVarCount;

	int mInstances;
	int mIterations;
	int mKeepBest;
	int mKeepWorst;
	int mCross;
	double mMutationFactor;

	double mBestSolution;
	double mStartTime;
	double mEndTime;
	int mFirstFeasibleIter;
};

