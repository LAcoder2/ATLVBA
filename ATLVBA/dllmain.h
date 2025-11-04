// dllmain.h: объявление класса модуля.

class CATLVBAModule : public ATL::CAtlDllModuleT< CATLVBAModule >
{
public :
	DECLARE_LIBID(LIBID_ATLVBALib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT1, "{566442d4-10d6-4437-b9d4-836bd6a64c04}")
};

extern class CATLVBAModule _AtlModule;
