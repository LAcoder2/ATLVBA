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
INT32 ArrLen(SAFEARRAY** ppsaAry) {
	return (*ppsaAry)->rgsabound[0].cElements;
}

//[ComExport]
INT32 StrLen(BSTR str) {
	if (str == NULL) return NULL;
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
int InStrByt(int Start, SAFEARRAY** ppsaWhere, SAFEARRAY** ppsaWhat) {
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

int InStrLenByt(int Start, SAFEARRAY** ppsaWhere, SAFEARRAY** ppsaWhat, int Length) {	
	INSTRBYT_VARPREP;
	INSTR_START_VALIDATION;
	INSTR_LEN_VALIDATION;

	BYTE_SEARCH_LOOP;

	return 0;
}

int InStrEndByt(int Start, SAFEARRAY** ppsaWhere, SAFEARRAY** ppsaWhat, int Stop) {	
	INSTRBYT_VARPREP;
	INSTR_START_VALIDATION;
	INSTR_STOP_VALIDATION;

	BYTE_SEARCH_LOOP;

	return 0;
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

