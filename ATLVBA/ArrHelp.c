#include "ATLVBA_i.h"
#include <windows.h>
//#include <oaidl.h>

short isObjInit(const void* Ary) { return *(short*)Ary; }

void __stdcall GetRefList(SAFEARRAY** ppsavRefsSrc, SAFEARRAY** ppsaRefsOut) {
	*ppsaRefsOut = *ppsavRefsSrc;
	*ppsavRefsSrc = SafeArrayCreateVector(VT_VARIANT, 0, 0);
}
HRESULT __stdcall PutRefList(SAFEARRAY** ppsavRefsDst, SAFEARRAY** ppsavRefsSrc) {
	VARIANT* pVDst = (VARIANT*)(*ppsavRefsDst)->pvData;
	VARIANT* pVSrc = (VARIANT*)(*ppsavRefsSrc)->pvData;
	int minCnt = (*ppsavRefsSrc)->rgsabound[0].cElements;
	int arCnt = (*ppsavRefsDst)->rgsabound[0].cElements;

	// Вывод сообщения с значениями
	//char msg[100];
	//sprintf_s(msg, sizeof(msg), "arCnt: %d, minCnt: %d", arCnt, minCnt);
	//MessageBoxA(NULL, msg, "Debug Info", MB_OK | MB_ICONINFORMATION);

	if (minCnt > arCnt) minCnt = arCnt;

	while (minCnt--) {
		VariantCopy(pVDst++, pVSrc++);
	}
	return S_OK;
}
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