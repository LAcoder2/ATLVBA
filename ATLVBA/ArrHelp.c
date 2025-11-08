#include "ATLVBA_i.h"
#include <windows.h>
//#include <oaidl.h>

short isObjInit(const void* Ary) { return *(short*)Ary; }

LPSAFEARRAY GetRefList(SAFEARRAY** ppsavRefs) {
	LPSAFEARRAY ret = *ppsavRefs;
	*ppsavRefs = SafeArrayCreateVector(VT_VARIANT, 0, 0);
	return ret;
}
void PutRefList(SAFEARRAY** ppsavRefsDst, SAFEARRAY** ppsavRefsSrc) {
	LPSAFEARRAY psavRefsDst = *ppsavRefsDst;	
	VARIANT* pVDst = (psavRefsDst)->pvData;
	int arCnt = (psavRefsDst)->rgsabound[0].cElements;
	LPSAFEARRAY psavRefsSrc = *ppsavRefsSrc;
	VARIANT* pVSrc = (psavRefsSrc)->pvData;
	int minCnt = (psavRefsSrc)->rgsabound[0].cElements;
	if (minCnt <= arCnt) {} else { minCnt = arCnt; }
	
	for (; pVDst < pVDst + minCnt; pVDst++, pVSrc++) {
		VariantCopy(pVDst, pVSrc);
	}
}