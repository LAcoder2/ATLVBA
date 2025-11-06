

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ATLVBA.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __ATLVBA_i_h__
#define __ATLVBA_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ATLVBALib_LIBRARY_DEFINED__
#define __ATLVBALib_LIBRARY_DEFINED__

/* library ATLVBALib */
/* [version][uuid] */ 

typedef /* [public] */ void AnyType;

#define	NullPtr	( 0 )


EXTERN_C const IID LIBID_ATLVBALib;


#ifndef __MemHelp_MODULE_DEFINED__
#define __MemHelp_MODULE_DEFINED__


/* module MemHelp */
/* [dllname][uuid] */ 

/* [entry] */ void GetMemPtr( 
    const void *src,
    void *dst);

/* [entry] */ void GetMem1( 
    const void *src,
    void *dst);

/* [entry] */ void GetMem2( 
    const void *src,
    void *dst);

/* [entry] */ void GetMem4( 
    const void *src,
    void *dst);

/* [entry] */ void GetMem8( 
    const void *src,
    void *dst);

/* [entry] */ void GetMem16( 
    const void *src,
    void *dst);

/* [entry] */ void GetMemVT( 
    const void *src,
    void *dst);

/* [entry] */ void PutMemPtr( 
    void *dst,
    __int3264 src);

/* [entry] */ void PutMem1( 
    void *dst,
    byte src);

/* [entry] */ void PutMem2( 
    void *dst,
    short src);

/* [entry] */ void PutMem4( 
    void *dst,
    long src);

/* [entry] */ void PutMem8( 
    void *dst,
    CY src);

/* [entry] */ void PutMemLL( 
    void *dst,
    __int64 src);

/* [entry] */ void PutMemVT( 
    void *dst,
    VARIANT src);

/* [propget][entry] */ HRESULT __stdcall get_GetByt( 
    /* [in] */ void *Src,
    /* [retval][out] */ byte *bRetVal);

/* [propput][entry] */ HRESULT __stdcall put_PutByt( 
    /* [in] */ void *Dst,
    /* [in] */ byte bNewVal);

/* [propget][entry] */ HRESULT __stdcall get_GetInt( 
    /* [in] */ void *Src,
    /* [retval][out] */ short *iRetVal);

/* [propput][entry] */ HRESULT __stdcall put_PutInt( 
    /* [in] */ void *Dst,
    /* [in] */ short iNewVal);

/* [propget][entry] */ HRESULT __stdcall get_GetLng( 
    /* [in] */ void *Src,
    /* [retval][out] */ int *lRetVal);

/* [propput][entry] */ HRESULT __stdcall put_PutLng( 
    /* [in] */ void *Dst,
    /* [in] */ int lNewVal);

/* [helpstring][propget][entry] */ HRESULT __stdcall get_GetPtr( 
    /* [in] */ void *Src,
    /* [retval][out] */ __int3264 *pRetVal);

/* [propput][entry] */ HRESULT __stdcall put_PutPtr( 
    /* [in] */ void *Dst,
    /* [in] */ __int3264 pNewVal);

/* [propget][entry] */ HRESULT __stdcall get_StringPtr( 
    /* [in] */ BSTR *Src,
    /* [retval][out] */ __int3264 *pRetVal);

/* [propput][entry] */ HRESULT __stdcall put_StringPtr( 
    /* [in] */ BSTR *Src,
    /* [in] */ __int3264 pNewVal);

/* [propget][entry] */ HRESULT __stdcall get_SAPtr( 
    /* [in] */ SAFEARRAY * *Array,
    /* [retval][out] */ __int3264 *pRetVal);

/* [propput][entry] */ HRESULT __stdcall put_SAPtr( 
    /* [in] */ SAFEARRAY * *Array,
    /* [in] */ __int3264 pNewVal);

/* [propget][entry] */ HRESULT __stdcall get_GetCur( 
    /* [in] */ void *Src,
    /* [retval][out] */ CURRENCY *cRetVal);

/* [propput][entry] */ HRESULT __stdcall put_PutCur( 
    /* [in] */ void *Dst,
    /* [in] */ CURRENCY cNewVal);

/* [propget][entry] */ HRESULT __stdcall get_GetDbl( 
    /* [in] */ void *Src,
    /* [retval][out] */ double *dRetVal);

/* [propput][entry] */ HRESULT __stdcall put_PutDbl( 
    /* [in] */ void *Dst,
    /* [in] */ double dNewVal);

/* [entry] */ void MovePtr( 
    void *dst,
    void *src);

/* [helpstring][entry] */ void MoveAryPtr( 
    SAFEARRAY * *dst,
    SAFEARRAY * *src);

/* [entry] */ void MoveAry( 
    SAFEARRAY * *dst,
    SAFEARRAY * *src);

/* [entry] */ void MoveStr( 
    BSTR *dst,
    BSTR *src);

/* [entry] */ void MoveVT( 
    void *dst,
    void *src);

/* [entry] */ void SwapPtr( 
    void *var1,
    void *var2);

/* [entry] */ void SwapAry( 
    SAFEARRAY * *var1,
    SAFEARRAY * *var2);

/* [entry] */ void SwapVT( 
    VARIANT *var1,
    VARIANT *var2);

/* [entry] */ long __stdcall memCmp( 
    const void *Buf1,
    const void *Buf2,
    __int3264 Size);

/* [entry] */ __int3264 __stdcall memCpy( 
    void *dst,
    const void *src,
    __int3264 sz);

#endif /* __MemHelp_MODULE_DEFINED__ */


#ifndef __StrHelp_MODULE_DEFINED__
#define __StrHelp_MODULE_DEFINED__


/* module StrHelp */


/* [entry] */ INT32 StrLen( 
    BSTR str);

/* [entry] */ INT32 StrLenB( 
    BSTR str);

/* [entry] */ BSTR ToAnsi( 
    BSTR str);

/* [entry] */ BSTR FromAnsi( 
    BSTR str);

/* [entry] */ INT32 InStrByt( 
    int Start,
    SAFEARRAY * *Where,
    SAFEARRAY * *What);

#endif /* __StrHelp_MODULE_DEFINED__ */


#ifndef __CallHelp_MODULE_DEFINED__
#define __CallHelp_MODULE_DEFINED__


/* module CallHelp */


/* [entry] */ void __stdcall Call0( 
    __int3264 fn,
    void *ret,
    int retSz);

/* [entry] */ void __stdcall Call1( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1);

/* [entry] */ void __stdcall Call2( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2);

/* [entry] */ void __stdcall Call3( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3);

/* [entry] */ void __stdcall Call4( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4);

/* [entry] */ void __stdcall Call5( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5);

/* [entry] */ void __stdcall Call6( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6);

/* [entry] */ void __stdcall Call7( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7);

/* [entry] */ void __stdcall Call8( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7,
    void *a8);

/* [entry] */ void __stdcall Call9( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7,
    void *a8,
    void *a9);

/* [entry] */ void __stdcall Call10( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7,
    void *a8,
    void *a9,
    void *a10);

/* [entry] */ void __stdcall CCall0( 
    __int3264 fn,
    void *ret,
    int retSz);

/* [entry] */ void __stdcall CCall1( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1);

/* [entry] */ void __stdcall CCall2( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2);

/* [entry] */ void __stdcall CCall3( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3);

/* [entry] */ void __stdcall CCall4( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4);

/* [entry] */ void __stdcall CCall5( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5);

/* [entry] */ void __stdcall CCall6( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6);

/* [entry] */ void __stdcall CCall7( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7);

/* [entry] */ void __stdcall CCall8( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7,
    void *a8);

/* [entry] */ void __stdcall CCall9( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7,
    void *a8,
    void *a9);

/* [entry] */ void __stdcall CCall10( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2,
    void *a3,
    void *a4,
    void *a5,
    void *a6,
    void *a7,
    void *a8,
    void *a9,
    void *a10);

/* [helpstring][entry] */ void __stdcall Call2_( 
    __int3264 fn,
    void *ret,
    int retSz,
    void *a1,
    void *a2);

#endif /* __CallHelp_MODULE_DEFINED__ */


#ifndef __LibHelp_MODULE_DEFINED__
#define __LibHelp_MODULE_DEFINED__


/* module LibHelp */
/* [helpstring][dllname] */ 

/* [entry] */ __int3264 __stdcall LoadLibW( 
    /* [in] */ BSTR LibFileName);

/* [entry] */ long FreeLib( 
    /* [in] */ __int3264 hLibModule);

/* [entry] */ __int3264 GetProcAddr( 
    /* [in] */ __int3264 hModule,
    /* [in] */ BSTR AnsiProcName);

#endif /* __LibHelp_MODULE_DEFINED__ */
#endif /* __ATLVBALib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


