#include "stdafx.h"
#include "task_4.h"
#include "solver.h"

using namespace std;

int main(int argc, char* argv[]) {

	if(argc != 9) {
		cerr << "Expected format is task_4 inst.dat sol.dat instances iterations keepBest keepWorst cross mutationFactor" << endl;
		return 2;
	}

	string inputFname(argv[1]);
	string solFname(argv[2]);

	int mInstances = 500;
	int mIterations = 10000;
	int mKeepBest = 50;
	int mKeepWorst = 25;
	int mCross = 150;
	double mMutationFactor = 0.05;

	{ istringstream is(argv[3]); is >> mInstances; }
	{ istringstream is(argv[4]); is >> mIterations; }
	{ istringstream is(argv[5]); is >> mKeepBest; }
	{ istringstream is(argv[6]); is >> mKeepWorst; }
	{ istringstream is(argv[7]); is >> mCross; }
	{ istringstream is(argv[8]); is >> mMutationFactor; }

	ifstream input(inputFname);
	ifstream sol(solFname);
	if (!input.good()) {
		cerr << "Cannot open input file: " << inputFname << endl;
		return 2;
	} else if (!sol.good()) {
		cerr << "Cannot open solution file: " << solFname << endl;
		return 2;
	}

	cout << "Input file: " << inputFname << ", solution file: " << solFname << endl;
	cout << "Instances: " << mInstances << ", " << "Iterations: " << mIterations << ", " << "KeepBest: " << mKeepBest << ", " << "KeepWorst: " << mKeepWorst << ", " << "Cross: " << mCross << ", " << "MutationFactor: " << mMutationFactor << endl;

	if(mKeepBest + mKeepWorst + mCross > mInstances) {
		cerr << "Wrong total sum" << endl;
		return 2;
	}

	double totalTime = 0;
	double avgError = 0;
	int cnt = 50;
	for (int i = 0; i < cnt; i++) {

		int id = 0;
		int itemsCnt = 0;
		int capacity = 0;
		input >> id >> itemsCnt >> capacity;

		auto solver = new Solver(capacity, itemsCnt);
		solver->mInstances = mInstances;
		solver->mIterations = mIterations;
		solver->mKeepBest = mKeepBest;
		solver->mKeepWorst = mKeepWorst;
		solver->mCross = mCross;
		solver->mMutationFactor = mMutationFactor;

		double weight, price;
		for (int x = 0; x < itemsCnt; x++) {
			input >> weight >> price;
			solver->AddItem(weight, price);
		}

		int dummy, solution;
		sol >> dummy >> dummy >> solution;
		for (int x = 0; x < itemsCnt; x++)
			sol >> dummy;

		solver->Start(solution);
		auto time = solver->GetElapsedTime();
		auto best = solver->GetBestSolution();

		auto eps = (solution - best) / solution;
		avgError += eps;
		totalTime += time;
		cout << "Total best: " << best << endl;
		cout << "Time: " << time << endl;
		cout << "Error: " << 100 * eps << endl << endl;	
	}
	cout << "Avg. time: " << (totalTime / cnt) << endl;
	cout << "Total avg. error: " << (100 * avgError / cnt) << endl;

#ifdef _DEBUG
	cout << "Finished... press any key..." << endl;
	getc(stdin);
#endif
	return 0;
}
