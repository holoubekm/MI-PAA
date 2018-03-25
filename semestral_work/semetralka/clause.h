#ifndef __CLAUSE__
#define __CLAUSE__

class Instance;
class Clause {
public:
	Clause(int pA, int pB, int pC);
	bool Evaluate(Instance* pInstance);
	//void Compute();
	//Instance* Clone();
	//Instance* Mutate(double pFactor);
	//Instance* CrossInstances(Instance* pRhs);
	//~Instance();

	static bool Comparator(const Clause* pLhs, const Clause* pRhs);

public:
	int mInxA;
	bool mValA;
	int mInxB;
	bool mValB;
	int mInxC;
	bool mValC;
};

#endif
