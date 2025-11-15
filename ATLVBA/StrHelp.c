#include "ATLVBA_i.h"
//#include <string.h>
#include <windows.h>
//#include "framework.h"

BSTR ToAnsi(const BSTR str)
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
BSTR FromAnsi(const BSTR str)
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
INT32 StrLenB(const BSTR str) {
	if (str == NULL) return 0;
	return *((INT32*)str - 1);
}
INT32 ArrLen(const SAFEARRAY** ppsaAry) {
	return (*ppsaAry)->rgsabound[0].cElements;
}

//[ComExport]
INT32 StrLen(const BSTR str) {
	if (str == NULL) return 0;
	return *((INT32*)str - 1) / 2;	
}

#define INSTRBYT_VARPREP \
	int cntWhere = (*ppsaWhere)->rgsabound[0].cElements; \
	int cntWhat = (*ppsaWhat)->rgsabound[0].cElements; \
	char *pcWhere1 = (char*)(*ppsaWhere)->pvData; \
	char *pcWhat1 = (char*)(*ppsaWhat)->pvData; \
	char *pcWhat2 = pcWhat1 + 1; 
#define INSTR_START_VALIDATION \
	if (Start > 0) { \
		if (Start < cntWhere) { \
			Start = Start - 1; \
		} else { \
			return 0; \
		} \
	} \
	else if (Start == 0) {} \
	else { \
		Start = cntWhere + Start; \
		if (Start >= 0) {} \
		else { Start = 0; } \
	}
#define BYTE_SEARCH_LOOP \
    char *pcEndIter = pcWhere1 + cntWhere - cntWhat; \
    char *pcEndIter2 = pcWhat1 + cntWhat; \
    char cWhat1 = *pcWhat1; \
    for(char *pcWhere = pcWhere1 + Start; pcWhere <= pcEndIter; pcWhere++) { \
        if (*pcWhere == cWhat1) { \
            char *pcWhere_ = pcWhere; \
            for (char *pcWhat = pcWhat2; pcWhat < pcEndIter2; pcWhat++) { \
                pcWhere_++; \
                if (*pcWhere_ != *pcWhat) goto Nxt; \
            } \
            return (pcWhere - pcWhere1) + 1; \
        } \
    Nxt:; \
    }
#define INSTRB_VARPREP \
	int cntWhere = *((int*)psWhere - 1); \
	int cntWhat = *((int*)psWhat - 1); \
	char *pcWhere1 = (char*)psWhere; \
	char *pcWhat1 = (char*)psWhat; \
	char *pcWhat2 = pcWhat1 + 1;
#define INSTR_LEN_VALIDATION \
	if (Length > 0) {\
	int maxLen = Start + Length;\
	if (maxLen >= cntWhere) {}\
	else { cntWhere = maxLen; }\
	}
	//else if (Length < 0) { return 0; } //или генерация ошибки
#define INSTR_STOP_VALIDATION \
	if (Stop > 0) { \
	if (Stop < cntWhere) { cntWhere = Stop; } \
	}
	//else if (Stop < 0) { return 0; } //или генерация ошибки

int InStrB2(int Start, const BSTR psWhere, const BSTR psWhat) {
	//int cntWhere = *((int*)psWhere - 1);
	//int cntWhat = *((int*)psWhat - 1);
	//char *pcWhere1 = (char*)psWhere;
	//char *pcWhat1 = (char*)psWhat;
	//char *pcWhat2 = pcWhat1 + 1;
	INSTRB_VARPREP;
	INSTR_START_VALIDATION;
	
	BYTE_SEARCH_LOOP;

	return 0;
}
int InStrLenB(int Start, const BSTR psWhere, const BSTR psWhat, int Length) {
	INSTRB_VARPREP;
	INSTR_START_VALIDATION;
	INSTR_LEN_VALIDATION;
	
	BYTE_SEARCH_LOOP;

	return 0;
}
int InStrEndB(int Start, const BSTR psWhere, const BSTR psWhat, int Stop) {
	INSTRB_VARPREP;
	INSTR_START_VALIDATION;
	INSTR_STOP_VALIDATION;

	BYTE_SEARCH_LOOP;

	return 0;
}
int InStrByt(int Start, const SAFEARRAY** ppsaWhere, const SAFEARRAY** ppsaWhat) {
	//int cntWhere = (*ppsaWhere)->rgsabound[0].cElements;
	//int cntWhat = (*ppsaWhat)->rgsabound[0].cElements;
	//char *pcWhere1 = (char*)(*ppsaWhere)->pvData;
	//char *pcWhat1 = (char*)(*ppsaWhat)->pvData;
	//char *pcWhat2 = pcWhat1 + 1;
	/*if (Start > 0) {
		if (Start < cntWhere) {
			Start = Start - 1;
		} else { 
			return 0; 
		}
	}
	else if (Start == 0) {}
	else {
		Start = cntWhere + Start;
		if (Start >= 0) {}
		else { Start = 0; }
	}*/

	INSTRBYT_VARPREP;
	INSTR_START_VALIDATION;
	BYTE_SEARCH_LOOP;

	return 0;
}

int InStrLenByt(int Start, const SAFEARRAY** ppsaWhere, const SAFEARRAY** ppsaWhat, int Length) {
	INSTRBYT_VARPREP;
	INSTR_START_VALIDATION;
	INSTR_LEN_VALIDATION;

	BYTE_SEARCH_LOOP;

	return 0;
}

int InStrEndByt(int Start, const SAFEARRAY** ppsaWhere, const SAFEARRAY** ppsaWhat, int Stop) {	
	INSTRBYT_VARPREP;
	INSTR_START_VALIDATION;
	INSTR_STOP_VALIDATION;

	BYTE_SEARCH_LOOP;

	return 0;
}
BSTR UCaseA(const BSTR psInp) {
	int szInp = *((int*)psInp-1);
	BSTR psRet = SysAllocStringByteLen(psInp, szInp);
	CharUpperBuffA(psRet, szInp);
	return psRet;
}
BSTR LCaseA(const BSTR psInp) {
	int szInp = *((int*)psInp - 1);
	BSTR psRet = SysAllocStringByteLen(psInp, szInp);
	CharLowerBuffA(psRet, szInp);
	return psRet;
}
__inline LPSTR CreateUpperStringA(const LPCSTR psInp, int lenInp) {
	int szAlloc = lenInp + 1;
	LPSTR psTmp1 = (LPSTR)malloc(szAlloc);
	if (psTmp1 != NULL) {
		memcpy(psTmp1, psInp, szAlloc);
		CharUpperBuffA(psTmp1, lenInp);
	}
	return psTmp1;
}
#define CREATE_UPPER_STRING_A(psInp, szsInp) CreateUpperStringA((psInp), (szsInp))

__inline LPSTR CreateUpperStringW(const LPCWSTR psInp, int lenInp) {
	int szAlloc = lenInp * 2 + 2;
	LPCWSTR psTmp1 = (LPSTR)malloc(szAlloc);
	if (psTmp1 != NULL) {
		memcpy(psTmp1, psInp, szAlloc);
		CharUpperBuffW(psTmp1, lenInp);
	}
	return psTmp1;
}
//typedef enum CompareMethod {
//	BinaryCompare = 0,
//	TextCompare = 1
//};
#define INSTRREVB_VAR_PREPARE_B \
	const int szChr = 1; \
	int szCheck = *((int*)psCheck - 1); \
	int lnCheck = szCheck; \
	int szMatch = *((int*)psMatch - 1); \
	
#define INSTRREV_VAR_PREPARE_W \
	const int szChr = 2; \
	int szCheck = *((int*)psCheck - 1); \
	int lnCheck = szCheck/2; \
	int szMatch = *((int*)psMatch - 1); \

#define INSTRREV_START_VALIDATION /*Универсальный A/W*/\
	if (Start > 0){ \
		if (Start <= lnCheck) { \
		} else { \
			Start = lnCheck; \
		} \
	} else if (Start == 0) { \
		Start = lnCheck; \
	} else { \
		Start += lnCheck + 1; \
		if (Start >= 0) {} \
		else return 0; /*или генерация ошбики "недопустимый параметр"*/ \
	} \

#define INSTRREVB_COMP_VALIDATION_B \
	INT_PTR pcCheck; \
	char* pcMatch;\
	char *psTmp1 = NULL, *psTmp2 = NULL; \
	if (Compare == BinaryCompare) { \
		pcCheck = psCheck; \
		pcMatch = psMatch; \
	} \
	else { \
		psTmp1 = CreateUpperStringA(psCheck, szCheck); \
		psTmp2 = CreateUpperStringA(psMatch, szMatch); \
		pcCheck = psTmp1; \
		pcMatch = psTmp2; \
	} \

#define INSTRREV_COMP_VALIDATION_W \
	INT_PTR pcCheck; \
	WCHAR* pcMatch;\
	WCHAR *psTmp1 = NULL, *psTmp2 = NULL; \
	if (Compare == BinaryCompare) { \
		pcCheck = psCheck; \
		pcMatch = psMatch; \
	} \
	else { \
		psTmp1 = CreateUpperStringW(psCheck, szCheck); \
		psTmp2 = CreateUpperStringW(psMatch, szMatch); \
		pcCheck = psTmp1; \
		pcMatch = psTmp2; \
	} \

#define INSTRREV_LENGTH_VALIDATION /*Универсальный A/W*/ \
	if (Length > 0) { \
		if (Length < Start) { \
			int off = Start - Length; \
			pcCheck += off; \
			Start -=off; \
		} \
	} else if (Length = 0) { \
	} else { \
		return 0; /* или генерация ошбики "недопустимое значение Length"*/ \
	}\

#define INSTRREV_LOOP_RET_B \
	INT_PTR lpret = _MemFindRev(pcCheck, Start, pcMatch, szMatch); \
	 \
	if (Compare == 0) {} else { free(psTmp1); free(psTmp2); } \
	 \
	if (lpret) return (lpret - (INT_PTR)psCheck) + 1; \
	return 0; \

#define INSTRREV_LOOP_RET_W \
	INT_PTR lpret = _MemFindRevW(pcCheck, Start * szChr, pcMatch, szMatch); \
	 \
	if (Compare == 0) {} else { free(psTmp1); free(psTmp2); } \
	 \
	if (lpret) return (lpret - pcCheck)/2 + 1; \
	return 0; \

int InStrRevB(const BSTR psCheck, const BSTR psMatch, long Start, enum CompareMethod Compare) {		
	//if (Start > 0){
	//	if (Start <= szCheck) {
	//	} else {
	//		Start = szCheck;
	//	}
	//} else if (Start == 0) {
	//	Start = szCheck;
	//} else {
	//	Start += szCheck + 1;
	//	if (Start >= 0) {}
	//	else return 0; //или генерация ошбики "недопустимый параметр"
	//}	
	//INT_PTR pcCheck;
	//char* pcMatch;
	//char *psTmp1=NULL, *psTmp2=NULL;
	//if (Compare == BinaryCompare) {	
	//	pcCheck = psCheck;
	//	pcMatch = psMatch;
	//} else {
	//	psTmp1 = CreateUpperStringA(psCheck, szCheck); 
	//	psTmp2 = CreateUpperStringA(psMatch, szMatch); 
	//	pcCheck = psTmp1;
	//	pcMatch = psTmp2;
	//}	
	//char cMatch1 = *pcMatch;
	//char* pcMatch2 = pcMatch + 1;
	//char* pEndMatch = pcMatch + szMatch; 
	//for (char* pcCheck = pcCheck1 + Start - szMatch; pcCheck >= pcCheck1; pcCheck--) {
	//	if (*pcCheck != cMatch1) {}
	//	else {
	//		char* pcCheck_ = pcCheck + 1;
	//		for (pcMatch = pcMatch2; pcMatch < pEndMatch; pcMatch++, pcCheck_++) {
	//			if (*pcCheck_ == *pcMatch) {} else goto skip;				
	//		}
	//		if (Compare == 0) {} else { free(psTmp1); free(psTmp2); }
	//		return (pcCheck - pcCheck1) + 1;
	//	}
	//skip:;
	//}	
	INSTRREVB_VAR_PREPARE_B;
	INSTRREV_START_VALIDATION;
	INSTRREVB_COMP_VALIDATION_B;
	INSTRREV_LOOP_RET_B;
}

int InStrLenRevB(BSTR psCheck, const BSTR psMatch, long Start, long Length, enum CompareMethod Compare) {
	INSTRREVB_VAR_PREPARE_B;
	INSTRREV_START_VALIDATION;
	INSTRREVB_COMP_VALIDATION_B;
	
	INSTRREV_LENGTH_VALIDATION;
	
	INSTRREV_LOOP_RET_B;
	
	/*INT_PTR lpret = _MemFindRev(pcCheck, Start, pcMatch, szMatch);		
	
	if (Compare == 0) {}
	else { free(psTmp1); free(psTmp2); }
		
	if (lpret) return (lpret - (INT_PTR)psCheck) + 1;
	return 0*/;

	//INT_PTR lpret = _MemFindRev(pcCheck, Start, pcMatch, szMatch);
	//if (Compare == BinaryCompare) {} else { free(psTmp1); free(psTmp2); }
	//if (lpret) return (lpret - pcCheck) + 1;
	//return 0;	
}

INT_PTR MemFindRev(char* pcWhere, int szWhere, char* pcWhat, int szWhat) {
	return _MemFindRevAuto(pcWhere, szWhere, pcWhat, szWhat);
}
__inline INT_PTR _MemFindRev(char* pcWhere, int szWhere, char* pcWhat, int szWhat) {
	char* pcWhere1 = pcWhere;
	char cWhat1 = *pcWhat;
	char* pcWhat2 = pcWhat + 1;
	char* pEndWhat = pcWhat + szWhat;
	for (pcWhere = pcWhere1 + szWhere - szWhat; pcWhere >= pcWhere1; pcWhere--) {
		if (*pcWhere != cWhat1) {}
		else {
			char* pcWhere_ = pcWhere + 1;
			for (pcWhat = pcWhat2; pcWhat < pEndWhat; pcWhat++, pcWhere_++) {
				if (*pcWhere_ == *pcWhat) {}
				else goto skip;
			}
			return (INT_PTR)pcWhere;
		}
	skip:;
	}
	return NULL;
}

INT_PTR MemFindRevW(const WCHAR* pcWhere, int szWhere, const WCHAR* pcWhat, int szWhat) {
	return _MemFindRevAuto(pcWhere, szWhere, pcWhat, szWhat);
}
__inline INT_PTR _MemFindRevW(WCHAR* pcWhere, int lnWhere, WCHAR* pcWhat, int lnWhat) {
	WCHAR* pcWhere1 = pcWhere;
	WCHAR cWhat1 = *pcWhat;
	WCHAR* pcWhat2 = pcWhat + 1;
	WCHAR* pEndWhat = pcWhat + lnWhat;
	for (pcWhere = pcWhere1 + lnWhere - lnWhat; pcWhere >= pcWhere1; pcWhere--) {
		if (*pcWhere != cWhat1) {}
		else {
			WCHAR* pcWhere_ = pcWhere + 1;
			for (pcWhat = pcWhat2; pcWhat < pEndWhat; pcWhat++, pcWhere_++) {
				if (*pcWhere_ == *pcWhat) {}
				else goto skip;
			}
			return (INT_PTR)pcWhere;
		}
	skip:;
	}
	return NULL;
}

__forceinline INT_PTR _MemFindRevAuto(auto* pcWhere, int lnWhere, auto* pcWhat, int lnWhat) {
	auto* pcWhere1 = pcWhere;
	auto cWhat1 = *pcWhat;
	auto* pcWhat2 = pcWhat + 1;
	auto* pEndWhat = pcWhat + lnWhat;
	for (pcWhere = pcWhere1 + lnWhere - lnWhat; pcWhere >= pcWhere1; pcWhere--) {
		if (*pcWhere != cWhat1) {}
		else {
			auto* pcWhere_ = pcWhere + 1;
			for (pcWhat = pcWhat2; pcWhat < pEndWhat; pcWhat++, pcWhere_++) {
				if (*pcWhere_ == *pcWhat) {}
				else goto skip;
			}
			return (INT_PTR)pcWhere;
		}
	skip:;
	}
	return NULL;
}


BSTR ToUTF8(const BSTR sInp){
	if (sInp == NULL) return NULL;
	int srcLen = *((int*)sInp - 1) / 2;
	if (srcLen == 0) return NULL; 

	int utf8Len = WideCharToMultiByte(CP_UTF8, 0, sInp, srcLen, NULL, 0, NULL, NULL);
	//if (utf8Len == 0) return NULL;
	BSTR result = SysAllocStringByteLen(NULL, utf8Len);
	if (result == NULL) return NULL;

	// Конвертируем Unicode в UTF-8
	WideCharToMultiByte(CP_UTF8, 0, sInp, srcLen, (char*)result, utf8Len, NULL, NULL);
	return result;
}
BSTR FromUTF8(const BSTR sInp){
	if (sInp == NULL) return NULL;
	int srcLen = *((int*)sInp - 1);
	if (srcLen == 0) return NULL;

	int wideLen = MultiByteToWideChar(CP_UTF8, 0, (char*)sInp, srcLen, NULL, 0);
	//if (wideLen == 0) return NULL;
	BSTR result = SysAllocStringLen(NULL, wideLen);
	if (result == NULL) return NULL;

	// Конвертируем UTF-8 в Unicode
	MultiByteToWideChar(CP_UTF8, 0, (char*)sInp, srcLen, result, wideLen);
	return result;
}

//Private Function ToUTF8(sText As String) As String 
//    Dim Ln As Long
//    Ln = WideCharToMultiByte(CP_UTF8, 0, StrPtr(sText), Len(sText), 0, 0, 0, 0)
//    If Ln Then
//        ToUTF8 = MidB$(String$(Ln \ 2 + 1, vbNullChar), 1, Ln)
//        WideCharToMultiByte CP_UTF8, 0, StrPtr(sText), Len(sText), StrPtr(ToUTF8), Ln, 0, 0
//    End If
//End Function
//Public Function FromUTF8(sText As String) As String 'utf8(1byte) to unicode(2byte)
//    Dim Ln As Long
//    Ln = MultiByteToWideChar(CP_UTF8, 0, StrPtr(sText), LenB(sText), 0, 0)
//    If Ln Then
//        FromUTF8 = String(Ln, vbNullChar)
//        MultiByteToWideChar CP_UTF8, 0, StrPtr(sText), LenB(sText), StrPtr(FromUTF8), Ln
//    End If
//End Function

//int InStrByt(int Start, SAFEARRAY** ppsaWhere, SAFEARRAY** ppsaWhat) {
//	int cntWhere = (*ppsaWhere)->rgsabound[0].cElements;
//	int cntWhat = (*ppsaWhat)->rgsabound[0].cElements;
//	char *pcWhere1 = (char*)(*ppsaWhere)->pvData;
//	char *pcWhat1 = (char*)(*ppsaWhat)->pvData;
//	char *pcWhat2 = pcWhat1 + 1;
//	
//	/*if (Start > 0) {
//		if (Start < cntWhere) {}else{return 0;}
//	}
//	else if (Start == 0) {
//		Start = 1;
//	}
//	else {
//		Start = cntWhere + Start + 1;
//		if (Start > 0) {}else {Start = 1;}
//	}*/
//	if (Start > 0) {
//		if (Start < cntWhere) {
//			Start = Start - 1;
//		}else{ 
//			return 0; 
//		}
//	}
//	else if (Start == 0) {
//		//Start = 0;
//	}
//	else {
//		Start = cntWhere + Start; //+ 1;
//		if (Start >= 0) {}
//		else { Start = 0; }
//	}
//	
//	char *pcEndIter = pcWhere1 + cntWhere - cntWhat;
//	char *pcEndIter2 = pcWhat1 + cntWhat; //- 1;
//	char cWhat1 = *pcWhat1;	
//	for(char *pcWhere = pcWhere1 + Start; pcWhere <= pcEndIter; pcWhere++) {
//		if (*pcWhere == cWhat1) {			
//			char *pcWhere_ = pcWhere;			
//			for (char *pcWhat = pcWhat2; pcWhat < pcEndIter2; pcWhat++) {
//				pcWhere_++;
//				if (*pcWhere_ != *pcWhat) goto Nxt;
//			}
//			return (pcWhere - pcWhere1) + 1;
//		}
//	Nxt:;
//	}
//	return 0;
//}

