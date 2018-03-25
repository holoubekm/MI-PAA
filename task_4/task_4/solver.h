#pragma once
#include <string>

using namespace std;

class Knapsack;
class Solver
{
public:
	Solver(int pCapacity, int pItemsCount);
	void AddItem(double mWeight, double mPrice);

	void Start(double pOptimalSolution);
	double GetElapsedTime();
	double GetBestSolution();
	~Solver();

public:
	Knapsack* mProblem;

	int mCapacity;
	int mItemsCount;
	int mItemsAdded;

	int mInstances;
	int mIterations;
	int mKeepBest;
	int mKeepWorst;
	int mCross;
	double mMutationFactor;

	double mBestSolution;
	double mStartTime;
	double mEndTime;
	double mRelativeError;
};

