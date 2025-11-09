#include "ATLVBA_i.h"
#include <windows.h>
//#include <oaidl.h>

short isObjInit(const void* Ary) { return *(short*)Ary; }

void __stdcall GetRefList(SAFEARRAY** ppsavRefsSrc, SAFEARRAY** ppsaRefsOut) {
	*ppsaRefsOut = *ppsavRefsSrc;
	*ppsavRefsSrc = SafeArrayCreateVector(VT_VARIANT, 0, 0);
}
void __stdcall AssignVecV(SAFEARRAY** ppsavRefsDst, SAFEARRAY** ppsavRefsSrc) {
	VARIANT* pVDst = (VARIANT*)(*ppsavRefsDst)->pvData;
	VARIANT* pVSrc = (VARIANT*)(*ppsavRefsSrc)->pvData;
	int minCnt = (*ppsavRefsSrc)->rgsabound[0].cElements;
	int arCnt = (*ppsavRefsDst)->rgsabound[0].cElements;
	
	if (minCnt > arCnt) minCnt = arCnt;

	while (minCnt--) {
		VariantCopy(pVDst++, pVSrc++);
	}
	//SafeArrayDestroy(*ppsavRefsSrc);
	//return S_OK;
}
void __stdcall AssignVec(SAFEARRAY** ppsaDst, SAFEARRAY** ppsaSrc) {
	VARIANT* pVDst = (VARIANT*)(*ppsaDst)->pvData;
	VARIANT* pVSrc = (VARIANT*)(*ppsaDst)->pvData;	
	int minCnt = (*ppsaDst)->rgsabound[0].cElements;
	int arCnt = (*ppsaDst)->rgsabound[0].cElements;
	if (minCnt > arCnt) minCnt = arCnt;

	while (minCnt--) {
		VariantCopy(pVDst++, pVSrc++);
	}
	//SafeArrayDestroy(*ppsavRefsSrc);
	//return S_OK;
}
//typedef void(*callback)(__int3264 dst, __int3264 src);
//static callback cfn;
//void InitCallBack(callback pfn) { cfn = pfn; }
//void __stdcall TestProp(SAFEARRAY** ppsavRefsDst, SAFEARRAY** ppsavRefsSrc) {
//	if (cfn) {} else { return; }
//	cfn(ppsavRefsDst, ppsavRefsSrc);
//	//SafeArrayDestroy(*ppsavRefsSrc);
//}
//void PutRefList(SAFEARRAY** ppsavRefsDst, SAFEARRAY** ppsavRefsSrc) {
//	//SAFEARRAY* psavRefsDst = *ppsavRefsDst;	
//	VARIANT* pVDst = (VARIANT*)(*ppsavRefsDst)->pvData;
//	int arCnt = (*ppsavRefsDst)->rgsabound[0].cElements;
//	//LPSAFEARRAY psavRefsSrc = *ppsavRefsSrc;
//	VARIANT* pVSrc = (VARIANT*)(*ppsavRefsSrc)->pvData;
//	//MessageBoxA(NULL, ";
//	int minCnt = (*ppsavRefsSrc)->rgsabound[0].cElements;
//	if (minCnt <= arCnt) {} else { minCnt = arCnt; }
//	
//	for (; pVDst < pVDst + minCnt; pVDst++, pVSrc++) {
//		VariantCopy(pVDst, pVSrc);
//	}
//}