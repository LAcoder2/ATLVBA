#include "ATLVBA_i.h"
//#include <string.h>
#include <windows.h>
BSTR ToAnsi(BSTR str)
{
	if (str == NULL) return NULL;

	DWORD size = *((DWORD*)str - 1);
	if (size == 0) return NULL;

	int wideLen = size / 2;

	int ansiLen = WideCharToMultiByte(CP_ACP, 0, str, wideLen, NULL, 0, NULL, NULL);
	if (ansiLen == 0) return NULL;

	BSTR result = SysAllocStringByteLen(NULL, ansiLen);
	if (result == NULL) return NULL;

	WideCharToMultiByte(CP_ACP, 0, str, wideLen, (char*)result, ansiLen, NULL, NULL);
	return result;
}
BSTR FromAnsi(BSTR str)
{
	if (str == NULL) return NULL;

	DWORD size = *((DWORD*)str - 1);
	if (size == 0) return NULL;

	int wideLen = MultiByteToWideChar(CP_ACP, 0, (char*)str, size, NULL, 0);
	if (wideLen == 0) return NULL;

	BSTR result = SysAllocStringLen(NULL, wideLen);
	if (result) {
		MultiByteToWideChar(CP_ACP, 0, (char*)str, size, result, wideLen);
	}
	return result;
}
//[ComExport]
INT32 StrLenB(BSTR str) {
	if (str == NULL) return NULL;
	return *((INT32*)str - 1);
}
//[ComExport]
INT32 StrLen(BSTR str) {
	if (str == NULL) return NULL;
	return *((INT32*)str - 1) / 2;	
}
//int InStrByt(int Start, SAFEARRAY** Where, SAFEARRAY** What) {
//	int cntWhere = (*Where)->rgsabound[0].cElements;
//	int cntWhat = (*What)->rgsabound[0].cElements;
//	char *pcWhat1 = (char*)(*What)->pvData;
//	char *pcWhat2 = pcWhat1 + 1;  // Исправлено
//
//	if (Start > 0) {
//		if (Start < cntWhere) {}else{return 0;}
//	}
//	else if (Start == 0) {
//		Start = 1;
//	}
//	else {
//		Start = cntWhere + Start + 1;
//		if (Start > 0) {}else {Start = 1;}
//	}
//
//	char *pcWhere = (char*)(*Where)->pvData;
//	char *pcEndIter = pcWhere + (cntWhere - cntWhat);
//	char *pcEndIter2 = pcWhat1 + cntWhat;
//	char cWhat1 = *pcWhat1;
//
//	char *current = pcWhere + Start - 1;  // Временный указатель
//	for (; current <= pcEndIter; current++) {
//		if (*current == cWhat1) {
//			char *search_ptr = current + 1;
//			char *pattern_ptr = pcWhat2;
//
//			for (; pattern_ptr < pcEndIter2; pattern_ptr++, search_ptr++) {
//				if (*search_ptr != *pattern_ptr) goto Nxt;
//			}
//			return (current - pcWhere) + 1;  // Исправлен расчет
//		}
//	Nxt:;
//	}
//	return 0;
//}
int InStrByt(int Start, SAFEARRAY** ppSAWhere, SAFEARRAY** ppSAWhat) {
	int cntWhere = (*ppSAWhere)->rgsabound[0].cElements;
	int cntWhat = (*ppSAWhat)->rgsabound[0].cElements;
	char *pcWhere1 = (char*)(*ppSAWhere)->pvData;
	char *pcWhat1 = (char*)(*ppSAWhat)->pvData;
	char *pcWhat2 = pcWhat1 + 1;
	
	if (Start > 0) {
		if (Start < cntWhere) {}else{return 0;}
	}
	else if (Start == 0) {
		Start = 1;
	}
	else {
		Start = cntWhere + Start + 1;
		if (Start > 0) {}else {Start = 1;}
	}
	
	char *pcEndIter = pcWhere1 + cntWhere - cntWhat;
	char *pcEndIter2 = pcWhat1 + cntWhat; //- 1;
	char cWhat1 = *pcWhat1;
	char *pcWhere = pcWhere1 + Start - 1;
	for(; pcWhere <= pcEndIter; pcWhere++) {
		if (*pcWhere == cWhat1) {			
			char *pcWhat = pcWhat2;
			for (; pcWhat < pcEndIter2; pcWhat++) {
				pcWhere++;
				if (*pcWhere != *pcWhat) goto Nxt;
			}
			return (pcWhere - pcWhere1) - cntWhat + 2;
		}
	Nxt:;
	}
	return 0;
}
	

//	For i = Start - 1 To cntWhere - cntWhat
//	If Where(i) = What1 Then
//	For l = l2 To ubWhat
//	i = i + 1
//	If Where(i) < > What(l) Then GoTo Nxt
//	Next
//
//	VBInStrByt = i - cntWhat + 2
//	Exit Function
//	End If
//	Nxt :
//Next
//End Function