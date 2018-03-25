#ifndef __GENERATION__
#define __GENERATION__

class Knapsack;

class Instance {
public:
	Instance(Knapsack* pInstance, int pItemsCount);
	void Compute();
	Instance* Clone();
	Instance* Mutate(double pFactor);
	~Instance();
	
	static bool Comparator(const Instance* pLhs, const Instance* pRhs);

public:
	bool* mItems;
	Knapsack* mInstance;
	int mItemsCount;
	double mWeight;
	double mPrice;
};

#endif
