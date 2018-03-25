#include "stdafx.h"
#include "semestralka.h"
#include "solver.h"
#include <set>
#include <unordered_map>

using namespace std;

int GetVarCount(ifstream& pInputFile, int pClausesCnt) {

	int A, B, C, Weight, varDummy, clausesDummy;
	set<int> clausesCnt;
	for (int x = 0; x < pClausesCnt; x++) {
		pInputFile >> A >> B >> C >> Weight;
		clausesCnt.insert(abs(A));
		clausesCnt.insert(abs(B));
		clausesCnt.insert(abs(C));
	}
	pInputFile.clear();
	pInputFile.seekg(0, ios::beg);
	pInputFile >> varDummy >> clausesDummy;
	return clausesCnt.size();
}

int main(int argc, char* argv[]) {

	if(argc != 7 && argc != 8) {
		cerr << "Expected format is semetralka instances iterations keepBest keepWorst cross mutationFactor [clausesCount]" << endl;
		return 2;
	}

	int mInstances = 500;
	int mIterations = 10000;
	int mKeepBest = 50;
	int mKeepWorst = 25;
	int mCross = 150;
	int mMaxClauses = 500;
	double mMutationFactor = 0.05;

	{ istringstream is(argv[1]); is >> mInstances; }
	{ istringstream is(argv[2]); is >> mIterations; }
	{ istringstream is(argv[3]); is >> mKeepBest; }
	{ istringstream is(argv[4]); is >> mKeepWorst; }
	{ istringstream is(argv[5]); is >> mCross; }
	{ istringstream is(argv[6]); is >> mMutationFactor; }
	if(argc == 8)
	{ istringstream is(argv[7]); is >> mMaxClauses; }

	cout << "Instances: " << mInstances << ", " << "Iterations: " << mIterations << ", " << "KeepBest: " << mKeepBest << ", " << "KeepWorst: " << mKeepWorst << ", " << "Cross: " << mCross << ", " << "MutationFactor: " << mMutationFactor << ", " << "MaxClauses: " << mMaxClauses << endl;

	if(mKeepBest + mKeepWorst + mCross > mInstances) {
		cerr << "Wrong total sum" << endl;
		return 2;
	}

	double totalTime = 0;
	double fstIterSum = 0;
	double bestSum = 0;
	int cnt = 100;
	int fstIters = 0;
	int bests = 0;
	for (int i = 0; i < cnt; i++) {
		ostringstream os; 
		os << "instances/_uf250-0" << i << ".cnf";
		// os << "insts/200.dimacs";
		string inputFname = os.str();

		cout << "Input file: " << inputFname << endl;
		ifstream input(inputFname);
		if (!input.good()) {
			cerr << "Cannot open input file: " << inputFname << endl;
			return 2;
		}

		int varCount = 0;
		int clausesCount;
		input >> varCount >> clausesCount;
		
		if(mMaxClauses != 0) {
			clausesCount = clausesCount > mMaxClauses ? mMaxClauses : clausesCount;
		}
		

		// cout << "varCount: " << varCount << endl;
		varCount = GetVarCount(input, clausesCount);
		// cout << "varCount: " << varCount << endl;

		auto solver = new Solver(clausesCount, varCount);
		solver->mInstances = mInstances;
		solver->mIterations = mIterations;
		solver->mKeepBest = mKeepBest;
		solver->mKeepWorst = mKeepWorst;
		solver->mCross = mCross;
		solver->mMutationFactor = mMutationFactor;

		int pA = 0;
		int pB = 0;
		int pC = 0;
		int pWeight;
		
		unordered_map<int, int> hash;
		int added = 0;

		for (int x = 0; x < clausesCount; x++) {
			input >> pA >> pB >> pC >> pWeight;
			if(hash.find(abs(pA)) == hash.end())
				hash.insert({abs(pA), added++});

			if(hash.find(abs(pB)) == hash.end())
				hash.insert({abs(pB), added++});

			if(hash.find(abs(pC)) == hash.end())
				hash.insert({abs(pC), added++});

			pA = hash.find(abs(pA))->second * (pA < 0 ? -1 : 1);
			pB = hash.find(abs(pB))->second * (pB < 0 ? -1 : 1);
			pC = hash.find(abs(pC))->second * (pC < 0 ? -1 : 1);

			solver->AddClause(pA, pB, pC);
		}

		solver->Start();
		auto time = solver->GetElapsedTime();
		auto best = solver->GetBestSolution();
		auto fstIter = solver->GetFirstFeasibleIter();
		totalTime += time;

		if(fstIter != 0) {
			fstIterSum += fstIter;
			fstIters++;
		}
		if(best != 0) {
			bestSum += best;
			bests++;
		}
		cout << "Total best: " << best << endl;
		cout << "FirstFeasibleIteration: " << fstIter << endl;
		cout << "Time: " << time << endl;
	}
	cout << "Avg. bestSol: " << (bestSum / bests) << endl;
	cout << "Avg. fstFeasible: " << (fstIterSum / fstIters) << endl;
	cout << "Avg. time: " << (totalTime / cnt) << endl;

#ifdef _DEBUG
	cout << "Finished... press any key..." << endl;
	getc(stdin);
#endif
	return 0;
}
