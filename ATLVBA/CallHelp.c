#include "ATLVBA_i.h"
#include <windows.h>
#include "Initialization.h"

typedef INT64(__stdcall *fun0)();
typedef INT64(__stdcall *fun1)(void*);
typedef INT64(__stdcall *fun2)(void*, void*);
typedef INT64(__stdcall *fun3)(void*, void*, void*);
typedef INT64(__stdcall *fun4)(void*, void*, void*, void*);
typedef INT64(__stdcall *fun5)(void*, void*, void*, void*, void*);
typedef INT64(__stdcall *fun6)(void*, void*, void*, void*, void*, void*);
typedef INT64(__stdcall *fun7)(void*, void*, void*, void*, void*, void*, void*);
typedef INT64(__stdcall *fun8)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef INT64(__stdcall *fun9)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef INT64(__stdcall *fun10)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__stdcall *sub0)();
typedef void(__stdcall *sub1)(void*);
typedef void(__stdcall *sub2)(void*, void*);
typedef void(__stdcall *sub3)(void*, void*, void*);
typedef void(__stdcall *sub4)(void*, void*, void*, void*);
typedef void(__stdcall *sub5)(void*, void*, void*, void*, void*);
typedef void(__stdcall *sub6)(void*, void*, void*, void*, void*, void*);
typedef void(__stdcall *sub7)(void*, void*, void*, void*, void*, void*, void*);
typedef void(__stdcall *sub8)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__stdcall *sub9)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__stdcall *sub10)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__stdcall *sub11)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);

void Call0(INT_PTR fn, void* ret, int retSz){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun0)fn)();
			memcpy(ret, &ret64, retSz);
		}else{
			((sub1)fn)(ret);
		}
	}else{
		((sub0)fn)();
	}
}
void Call1(INT_PTR fn, void* ret, int retSz, void* a1){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun1)fn)(a1);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub2)fn)(ret, a1);
		}
	}else{
		((sub1)fn)(a1);
	}
}
//!!!!!!!!!!!##############!!!!!!!!!!!!!##############
typedef struct { byte bytes[3]; } _3B;
typedef struct { byte bytes[5]; } _5B;
typedef struct { byte bytes[6]; } _6B;
typedef struct { byte bytes[7]; } _7B;
void copy0(void* dst, void* src) {}
void copy1(void* dst, void* src) { *(byte*)(dst) = *(byte*)(src); }
void copy2(void* dst, void* src) { *(INT16*)(dst) = *(INT16*)(src); }
void copy3(void* dst, void* src) { *(_3B*)(dst) = *(_3B*)(src); }
void copy4(void* dst, void* src) { *(INT32*)(dst) = *(INT32*)(src); }
void copy5(void* dst, void* src) { *(_5B*)(dst) = *(_5B*)(src); }
void copy6(void* dst, void* src) { *(_6B*)(dst) = *(_6B*)(src); }
void copy7(void* dst, void* src) { *(_7B*)(dst) = *(_7B*)(src); }
void copy8(void* dst, void* src) { *(INT64*)(dst) = *(INT64*)(src); }
typedef void(*copyDlg)(void* dst, void* src);
copyDlg copyFnArr[9];
void __cdecl initCopyFnArr() { //cdecl указан для запуска функции в файле dllmain.cpp для которого по умолчаню задан тип запуска cdecl
	copyFnArr[0] = copy0;
	copyFnArr[1] = copy1;
	copyFnArr[2] = copy2;
	copyFnArr[3] = copy3;
	copyFnArr[4] = copy4;
	copyFnArr[5] = copy5;
	copyFnArr[6] = copy6;
	copyFnArr[7] = copy7;
	copyFnArr[8] = copy8;
}
//__declspec(dllexport)
void Call2_(INT_PTR fn, void* ret, int retSz, void* a1, void* a2) {
	if (retSz > -1) {} else  return;
	if (ret != NULL) {
		if (retSz <= 8) {
			INT64 ret64 = ((fun2)fn)(a1, a2);			
			copyFnArr[retSz](ret, ret64);		//memcpy(ret, &ret64, retSz);
		} else {
			((sub3)fn)(ret, a1, a2);
		}
	} else {
		((sub2)fn)(a1, a2);
	}
}
void Call2(INT_PTR fn, void* ret, int retSz, void* a1, void* a2){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun2)fn)(a1, a2);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub3)fn)(ret, a1, a2);
		}
	}else{
		((sub2)fn)(a1, a2);
	}
}
void Call3(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun3)fn)(a1, a2, a3);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub4)fn)(ret, a1, a2, a3);
		}
	}else{
		((sub3)fn)(a1, a2, a3);
	}
}
void Call4(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun4)fn)(a1, a2, a3, a4);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub5)fn)(ret, a1, a2, a3, a4);
		}
	}else{
		((sub4)fn)(a1, a2, a3, a4);
	}
}
void Call5(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun5)fn)(a1, a2, a3, a4, a5);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub6)fn)(ret, a1, a2, a3, a4, a5);
		}
	}else{
		((sub5)fn)(a1, a2, a3, a4, a5);
	}
}
void Call6(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun6)fn)(a1, a2, a3, a4, a5, a6);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub7)fn)(ret, a1, a2, a3, a4, a5, a6);
		}
	}else{
		((sub6)fn)(a1, a2, a3, a4, a5, a6);
	}
}
void Call7(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun7)fn)(a1, a2, a3, a4, a5, a6, a7);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub8)fn)(ret, a1, a2, a3, a4, a5, a6, a7);
		}
	}else{
		((sub7)fn)(a1, a2, a3, a4, a5, a6, a7);
	}
}
void Call8(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun8)fn)(a1, a2, a3, a4, a5, a6, a7, a8);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub9)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8);
		}
	}else{
		((sub8)fn)(a1, a2, a3, a4, a5, a6, a7, a8);
	}
}
void Call9(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun9)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub10)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}
	}else{
		((sub9)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}
}
void Call10(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((fun10)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
			memcpy(ret, &ret64, retSz);
		}else{
			((sub11)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
		}
	}else{
		((sub10)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	}
}
//########################CDECL Section########################
typedef INT64(__cdecl *cfun0)();
typedef INT64(__cdecl *cfun1)(void*);
typedef INT64(__cdecl *cfun2)(void*, void*);
typedef INT64(__cdecl *cfun3)(void*, void*, void*);
typedef INT64(__cdecl *cfun4)(void*, void*, void*, void*);
typedef INT64(__cdecl *cfun5)(void*, void*, void*, void*, void*);
typedef INT64(__cdecl *cfun6)(void*, void*, void*, void*, void*, void*);
typedef INT64(__cdecl *cfun7)(void*, void*, void*, void*, void*, void*, void*);
typedef INT64(__cdecl *cfun8)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef INT64(__cdecl *cfun9)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef INT64(__cdecl *cfun10)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__cdecl *csub0)();
typedef void(__cdecl *csub1)(void*);
typedef void(__cdecl *csub2)(void*, void*);
typedef void(__cdecl *csub3)(void*, void*, void*);
typedef void(__cdecl *csub4)(void*, void*, void*, void*);
typedef void(__cdecl *csub5)(void*, void*, void*, void*, void*);
typedef void(__cdecl *csub6)(void*, void*, void*, void*, void*, void*);
typedef void(__cdecl *csub7)(void*, void*, void*, void*, void*, void*, void*);
typedef void(__cdecl *csub8)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__cdecl *csub9)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__cdecl *csub10)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void(__cdecl *csub11)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);

void CCall0(INT_PTR fn, void* ret, int retSz){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun0)fn)();
			memcpy(ret, &ret64, retSz);
		}else{
			((csub1)fn)(ret);
		}
	}else{
		((csub0)fn)();
	}
}
void CCall1(INT_PTR fn, void* ret, int retSz, void* a1){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun1)fn)(a1);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub2)fn)(ret, a1);
		}
	}else{
		((csub1)fn)(a1);
	}
}
void CCall2(INT_PTR fn, void* ret, int retSz, void* a1, void* a2){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun2)fn)(a1, a2);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub3)fn)(ret, a1, a2);
		}
	}else{
		((csub2)fn)(a1, a2);
	}
}
void CCall3(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun3)fn)(a1, a2, a3);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub4)fn)(ret, a1, a2, a3);
		}
	}else{
		((csub3)fn)(a1, a2, a3);
	}
}
void CCall4(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun4)fn)(a1, a2, a3, a4);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub5)fn)(ret, a1, a2, a3, a4);
		}
	}else{
		((csub4)fn)(a1, a2, a3, a4);
	}
}
void CCall5(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun5)fn)(a1, a2, a3, a4, a5);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub6)fn)(ret, a1, a2, a3, a4, a5);
		}
	}else{
		((csub5)fn)(a1, a2, a3, a4, a5);
	}
}
void CCall6(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun6)fn)(a1, a2, a3, a4, a5, a6);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub7)fn)(ret, a1, a2, a3, a4, a5, a6);
		}
	}else{
		((csub6)fn)(a1, a2, a3, a4, a5, a6);
	}
}
void CCall7(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun7)fn)(a1, a2, a3, a4, a5, a6, a7);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub8)fn)(ret, a1, a2, a3, a4, a5, a6, a7);
		}
	}else{
		((csub7)fn)(a1, a2, a3, a4, a5, a6, a7);
	}
}
void CCall8(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun8)fn)(a1, a2, a3, a4, a5, a6, a7, a8);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub9)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8);
		}
	}else{
		((csub8)fn)(a1, a2, a3, a4, a5, a6, a7, a8);
	}
}
void CCall9(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun9)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub10)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}
	}else{
		((csub9)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}
}
void CCall10(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10){
	if (ret != NULL){
		if (retSz <= 8){
			INT64 ret64 = ((cfun10)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
			memcpy(ret, &ret64, retSz);
		}else{
			((csub11)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
		}
	}else{
		((csub10)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	}
}

//#####################################################
//void Call0(INT_PTR fn, void* ret, int retSz){
//	typedef INT64(__stdcall *dlg1)();
//	typedef void(__stdcall *dlg2)(void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)();
//	}
//	else {
//		((dlg2)fn)(ret);
//	}
//}
//void Call1(INT_PTR fn, void* ret, int retSz, void* a1){
//	typedef INT64(__stdcall *dlg1)(void*);
//	typedef void(__stdcall *dlg2)(void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1);
//	}
//	else {
//		((dlg2)fn)(ret, a1);
//	}
//}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//typedef INT64(__stdcall *fun2)(void*, void*);
//typedef INT64(__stdcall *fun3)(void*, void*, void*);
//typedef void(__stdcall *sub2)(void*, void*);
//typedef void(__stdcall *sub3)(void*, void*, void*);
//void Call2(INT_PTR fn, void* ret, int retSz, void* a1, void* a2){
//	if (ret != NULL){
//		if (retSz <= 8){
//			INT64 ret64 = ((fun2)fn)(a1, a2);
//			memcpy(ret, &ret64, retSz);
//		}else{
//			//вызываем функцию как процедуру если размер возвращаемого значения >8
//			((sub3)fn)(ret, a1, a2); 
//		}
//	}else{
//		// вызываем как процедуру, если это процедура (void)
//		((sub2)fn)(a1, a2);  		
//	}
//}
////void Call2(INT_PTR fn, void* ret, int retSz, void* a1, void* a2){
////	typedef INT64(__stdcall *dlg1)(void*, void*);
////	typedef void(__stdcall *dlg2)(void*, void*, void*);
////	if (retSz <= 8){
////		*(INT64*)ret = ((dlg1)fn)(a1, a2);
////	}
////	else {
////		((dlg2)fn)(ret, a1, a2);
////	}
////}
//void Call3(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3);
//	}
//}
//void Call4(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4);
//	}
//}
//void Call5(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5);
//	}
//}
//void Call6(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6);
//	}
//}
//void Call7(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7);
//	}
//}
//void Call8(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7, a8);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8);
//	}
//}
//void Call9(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9);
//	}
//}
//void Call10(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10){
//	typedef INT64(__stdcall *dlg1)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	}
//}
////########################CDECL Section########################
//void CCall0(INT_PTR fn, void* ret, int retSz){
//	typedef INT64(__cdecl *dlg1)();
//	typedef void(__cdecl *dlg2)(void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)();
//	}
//	else {
//		((dlg2)fn)(ret);
//	}
//}
//void CCall1(INT_PTR fn, void* ret, int retSz, void* a1){
//	typedef INT64(__cdecl *dlg1)(void*);
//	typedef void(__cdecl *dlg2)(void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1);
//	}
//	else {
//		((dlg2)fn)(ret, a1);
//	}
//}
//void CCall2(INT_PTR fn, void* ret, int retSz, void* a1, void* a2){
//	typedef INT64(__cdecl *dlg1)(void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2);
//	}
//}
//void CCall3(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3);
//	}
//}
//void CCall4(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4);
//	}
//}
//void CCall5(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5);
//	}
//}
//void CCall6(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6);
//	}
//}
//void CCall7(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7);
//	}
//}
//void CCall8(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7, a8);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8);
//	}
//}
//void CCall9(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9);
//	}
//}
//void CCall10(INT_PTR fn, void* ret, int retSz, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10){
//	typedef INT64(__cdecl *dlg1)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	typedef void(__cdecl *dlg2)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	}
//	else {
//		((dlg2)fn)(ret, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//	}
//}

/*__declspec(dllexport)
INT_PTR CCall0(void* fn){
	typedef INT_PTR (__cdecl *c_func)();
	return ((c_func)fn)();
}
__declspec(dllexport)
INT_PTR CCall1(void* fn, void* arg1){
	typedef INT_PTR (__cdecl *c_func)(void*);
	return ((c_func)fn)(arg1);
}
__declspec(dllexport)
INT_PTR CCall2(void* fn, void* arg1, void* arg2){
	typedef INT_PTR (__cdecl *c_func)(void*, void*);
	return ((c_func)fn)(arg1, arg2);
}
__declspec(dllexport)
INT_PTR CCall3(void* fn, void* arg1, void* arg2, void* arg3){
	typedef INT_PTR (__cdecl *c_func)(void*, void*, void*);
	return ((c_func)fn)(arg1, arg2, arg3);
}
__declspec(dllexport)
INT_PTR CCall4(void* fn, void* arg1, void* arg2, void* arg3, void* arg4){
	typedef INT_PTR (__cdecl *c_func)(void*, void*, void*, void*);
	return ((c_func)fn)(arg1, arg2, arg3, arg4);
}
__declspec(dllexport)
INT_PTR CCall5(void* fn, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5){
	typedef INT_PTR (__cdecl *c_func)(void*, void*, void*, void*, void*);
	return ((c_func)fn)(arg1, arg2, arg3, arg4, arg5);
}*/

//void Call2(INT_PTR fn, void* ret, int retSz, void* arg1, void* arg2){
//	typedef INT64(__stdcall *dlg1)(void*, void*);
//	typedef void(__stdcall *dlg2)(void*, void*, void*);
//	if (retSz <= 8){
//		*(INT64*)ret = ((dlg1)fn)(arg1, arg2);
//	}
//	else {
//		((dlg2)fn)(ret, arg1, arg2);
//	}
//}
/*void Call2_(LONG_PTR fn, void* ret, int retSz, void* arg1, void* arg2){
	typedef __int64 (__stdcall *c_func1)(void*, void*);
	typedef void(__stdcall *c_func2)(void*, void*, void*);

	if (retSz <= 8){
		*reinterpret_cast<__int64*>(ret) = ((c_func1)fn)(arg1, arg2);
	}
	else {
		((c_func2)fn)(ret, arg1, arg2);
	}
}*/
//__declspec(dllexport)
//INT64 Call2_(INT_PTR fn, void* arg1, void* arg2){
//	typedef INT64(__stdcall *c_func)(void*, void*);
//	return ((c_func)fn)(arg1, arg2);
//}
//extern "C" __declspec(dllexport)
//__declspec(naked)
//void __stdcall Call2(void* pFun, void* pRet, size_t retSize, void* arg1, void* arg2)
//{
//	__asm {
//		push ebp
//		mov ebp, esp
//		push ebx
//		push edi

//		// Загружаем параметры
//		mov eax, [ebp + 8]   // pFun
//		mov ebx, [ebp + 12]  // pRet
//		mov edi, [ebp + 16]  // retSize

//		// Подготавливаем аргументы для целевой функции (stdcall)
//		push[ebp + 20]      // arg2
//		push[ebp + 24]      // arg1

//		// Вызываем целевую функцию
//		call eax

//		// Копируем возвращаемое значение в буфер pRet
//		cmp edi, 0
//		je done
//		cmp edi, 1
//		je copy_1
//		cmp edi, 2
//		je copy_2
//		cmp edi, 4
//		je copy_4
//		cmp edi, 8
//		je copy_8
//		jmp done

//		copy_1 :
//		mov byte ptr[ebx], al
//			jmp done
//			copy_2 :
//		mov word ptr[ebx], ax
//			jmp done
//			copy_4 :
//		mov dword ptr[ebx], eax
//			jmp done
//			copy_8 :
//		mov dword ptr[ebx], eax
//			mov dword ptr[ebx + 4], edx

//			done :
//		pop edi
//			pop ebx
//			pop ebp
//			ret 20  // 5 параметров × 4 байта = 20
//	}
//}
