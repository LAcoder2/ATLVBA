// dllmain.cpp: реализация DllMain.


#include "framework.h"
#include "resource.h"
#include "ATLVBA_i.h"
#include "dllmain.h"
#include "xdlldata.h"
#include "Initialization.h"

CATLVBAModule _AtlModule;

// Точка входа DLL
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	hInstance;

	switch (dwReason)	{
	case DLL_PROCESS_ATTACH:
		initCopyFnArr(); // Вызов инициализации при загрузке DLL
		break;
		// Можно добавить очистку при выгрузке, если нужно
	case DLL_PROCESS_DETACH:
		break;
	}

	return _AtlModule.DllMain(dwReason, lpReserved);
}
