#include "stdafx.h"
#include "clause.h"
#include "instance.h"

#define ABS(x) ((x > 0) ? x : -x)

Clause::Clause(int pA, int pB, int pC) :
	mInxA(ABS(pA)), mValA(pA >= 0),
	mInxB(ABS(pB)), mValB(pB >= 0),
	mInxC(ABS(pC)), mValC(pC >= 0) {

}

bool Clause::Evaluate(Instance* pInstance) {
	auto items = pInstance->mItems;
	return items[mInxA] == mValA || items[mInxB] == mValB || items[mInxC] == mValC;
}

bool Clause::Comparator(const Clause* pLhs, const Clause* pRhs) {
	return pLhs->mInxA == pRhs->mInxA &&
		pLhs->mInxB == pRhs->mInxB &&
		pLhs->mInxC == pRhs->mInxC &&
		pLhs->mValA == pRhs->mValA &&
		pLhs->mValB == pRhs->mValB &&
		pLhs->mValC == pRhs->mValC;
}
