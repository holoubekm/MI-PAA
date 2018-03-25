#ifndef __GENERATION__
#define __GENERATION__


class SAT3;

class Instance {
public:
	Instance(SAT3* pInstance, int pItemsCount);
	void Compute();
	Instance* Clone();
	Instance* Mutate(double pFactor);
	Instance* CrossInstances(Instance* pRhs);
	~Instance();
	
	static bool Comparator(const Instance* pLhs, const Instance* pRhs);

public:
	bool* mItems;
	SAT3* mSAT;
	int mVarCount;
	int mValue;
	bool mIsFeasible;

};

#endif
