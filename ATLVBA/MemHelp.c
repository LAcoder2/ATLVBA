#include "ATLVBA_i.h"
#include <windows.h>
#include <oaidl.h>
//#include "framework.h"
//#include "Initialization.h"
//constexpr VARIANT VEMPTY = {};			//c++
static const VARIANT VEMPTY = { VT_EMPTY };	//c
typedef struct {
	unsigned char bytes[16];
} _16Bytes;

void GetMem1(const byte* src, byte* dst) {*dst = *src;}
void GetMem2(const short* src, short* dst) {*dst = *src;}
void GetMem4(const INT32* src, INT32* dst) {*dst = *src;}
void GetMem8(const INT64* src, INT64* dst) {*dst = *src;}
void GetMem16(const _16Bytes* src, _16Bytes* dst) {*dst = *src;}
void GetMemVT(const VARIANT* src, VARIANT* dst) {*dst = *src;}
void GetMemPtr(const INT_PTR* src, INT_PTR* dst) {*dst = *src;}

void PutMem1(byte* dst, byte src) {*dst = src;}
void PutMem2(INT16* dst, INT16 src) {*dst = src;}
void PutMem4(INT32* dst, INT32 src) {*dst = src;}
void PutMem8(CURRENCY* dst, CURRENCY src) {*dst = src;}
void PutMemLL(INT64* dst, INT64 src) {*dst = src;}
void PutMemVT(VARIANT* dst, VARIANT src) {*dst = src;}
void PutMemPtr(INT_PTR* dst, INT_PTR src) {*dst = src;}

__int3264 VarPtr(const void* var) { return var; }

int memCmp(const void* buf1, const void* buf2, size_t Size) {return memcmp(buf1, buf2, Size);}
__int3264 memCpy(void* dst, const void* src, __int3264 sz) {return memcpy(dst, src, sz);}

void Copy16(_16Bytes* dst, _16Bytes* src) {*dst = *src;}

void MovePtr(INT_PTR* dst, INT_PTR* src) {
	*dst = *src;
	*src = NULL;
}
void MoveStr(BSTR* dst, BSTR* src) {
	if (*dst != NULL) SysFreeString(*dst);
	*dst = *src;
	*src = NULL;
}
void MoveAry(SAFEARRAY** dst, SAFEARRAY** src) {
	//if (*dst == *src) {			// если *dst и *src это один и тот же массив		
	//	*src = NULL;
	//	return;
	//}
	
	if (*dst != NULL) {			// если *dst инициализирован, освобождаем его
		SafeArrayDestroy(*dst);
	}
	*dst = *src;
	*src = NULL;
}
void MoveVT(VARIANT* dst, VARIANT* src) {
	if (dst->vt != VT_EMPTY || dst->vt != VT_NULL) {
		HRESULT hr = VariantClear(dst); // Ѕезопасно освобождаем VARIANT, если он не пустой
		//if (FAILED(hr)) {/*«десь можно обработать ошибку*/}
	}
	*dst = *src;
	*src = VEMPTY;
}

void SwapPtr(INT_PTR* var1, INT_PTR* var2) {
	INT_PTR tmp = *var1;
	*var1 = *var2;
	*var2 = tmp;
}
void SwapVT(VARIANT* var1, VARIANT* var2) {
	VARIANT tmp = *var1;
	*var1 = *var2;
	*var2 = tmp;
}
//void initCopyFnArr(); //тест экспорта
//void ExampleSub() {
//	initCopyFnArr();
//}

#define ROL(bitmask, n) (((bitmask) << (n)) | ((bitmask) >> (32 - (n))))

// Railgun_6pp by Georgi 'Sanmayce'
__int3264 memmem(char* pbTarget, long cbTarget, char* pbPattern, long cbPattern) {
	char * pbTargetMax = pbTarget + cbTarget;
	char * pbTargetMax2 = pbTargetMax - 8;
	unsigned long ulHashPattern = *(unsigned long *)(pbPattern);
	unsigned long ulHashTarget = *(unsigned long *)(pbTarget);

	if (cbPattern > cbTarget) return(NULL);

	if (cbPattern < 4) {
		// Use simple byte-by-byte search for very short patterns
		while (pbTarget <= pbTargetMax - cbPattern) {
			if (pbTarget[0] == pbPattern[0]) {
				if (cbPattern == 1) return(pbTarget);
				if (pbTarget[1] == pbPattern[1]) {
					if (cbPattern == 2) return(pbTarget);
					if (pbTarget[2] == pbPattern[2]) return(pbTarget);
				}
			}
			pbTarget++;
		}
		return(NULL);
	}

	// Main search loop
	while (pbTarget <= pbTargetMax2) {
		if (ulHashPattern == ulHashTarget) {
			// Potential match found, verify the rest
			if (pbTarget[4] == pbPattern[4] &&
				pbTarget[5] == pbPattern[5] &&
				pbTarget[6] == pbPattern[6] &&
				pbTarget[7] == pbPattern[7]) {
				// Full pattern verification
				if (memcmp(pbTarget + 8, pbPattern + 8, cbPattern - 8) == 0) {
					return(pbTarget);
				}
			}
		}

		// Update rolling hash
		ulHashTarget = ROL(ulHashTarget, 1) + pbTarget[4];
		pbTarget++;
		ulHashTarget = ROL(ulHashTarget, 1) + pbTarget[4];
	}

	// Check remaining positions
	while (pbTarget <= pbTargetMax - cbPattern) {
		if (memcmp(pbTarget, pbPattern, cbPattern) == 0) {
			return(pbTarget);
		}
		pbTarget++;
	}

	return(NULL);
}
