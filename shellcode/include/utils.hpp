#include<intrin.h>

#if defined(_WIN64)
#define _PEB_ __readgsqword
#define _PEB_Offset_1 0x30
#define _PEB_Offset_2 0x30
#define _Ldr_Offset_1 0x08
#define _Ldr_Offset_2 0x10
#define _List_Offset_1 0x08
#define _List_Offset_2 0x08
typedef DWORD64 _DWORD;
typedef PDWORD64 _PDWORD;
typedef PIMAGE_NT_HEADERS64 _PIMAGE_NT_HEADERS;
#else
#define _PEB_ __readfsword
#define _PEB_Offset_1 0x18
#define _PEB_Offset_2 0x18
#define _Ldr_Offset_1 0x06
#define _Ldr_Offset_2 0x06
#define _List_Offset_1 0x06
#define _List_Offset_2 0x06
typedef DWORD _DWORD;
typedef PDWORD _PDWORD;
typedef PIMAGE_NT_HEADERS _PIMAGE_NT_HEADERS;
#endif

#pragma warning(disable : 28251)
#pragma warning(disable : 6001)
#define INLINE __forceinline
extern "C" {
#pragma function(memset)
	void* __cdecl _memset(void* dest, int value, size_t num) {
		__stosb(static_cast<unsigned char*>(dest), static_cast<unsigned char>(value), num);
		return dest;
	}
#pragma function(memcpy)
	void* __cdecl _memcpy(void* dest, const void* src, size_t num) {
		__movsb(static_cast<unsigned char*>(dest), static_cast<const unsigned char*>(src), num);
		return dest;
	}
//#pragma function(strlen)
//	size_t __cdecl strlen(const char* str) {
//		size_t len = 0;
//		while (*str++) {
//			++len;
//		}
//		return len;
//	}
}

INLINE DWORD GetFuncHash(const char* functionName) {
	DWORD hash = 0;
	while (*functionName) {
		hash = (hash * 138) + *functionName;
		functionName++;
	}
	return hash;
}

INLINE _DWORD GetNtdllAddr() {
	_DWORD dwNtdll = 0;
	_TEB* pTeb = NtCurrentTeb();
	volatile _DWORD _peb_offset_1 = _PEB_Offset_1;
	volatile _DWORD _peb_offset_2 = _PEB_Offset_2;
	_DWORD pPeb = _PEB_(_peb_offset_1 + _peb_offset_2);
	volatile _DWORD _ldr_offset_1 = _Ldr_Offset_1;
	volatile _DWORD _ldr_offset_2 = _Ldr_Offset_2;
	_PDWORD pLdr = (_PDWORD) * (_PDWORD)((_DWORD)pPeb + _Ldr_Offset_1 + _Ldr_Offset_2);
	volatile _DWORD _list_offset_1 = _List_Offset_1;
	volatile _DWORD _list_offset_2 = _List_Offset_2;
	_PDWORD InLoadOrderModuleList = (_PDWORD)((_DWORD)pLdr + _list_offset_1 + _list_offset_2);
	_PDWORD pModuleExe = (_PDWORD)*InLoadOrderModuleList;
	_PDWORD pModuleNtdll = (_PDWORD)*pModuleExe;
	dwNtdll = pModuleNtdll[6];
	return dwNtdll;
}

INLINE _DWORD GetKernel32Addr() {
	_DWORD dwKernel32 = 0;
	_TEB* pTeb = NtCurrentTeb();
	volatile _DWORD _peb_offset_1 = _PEB_Offset_1;
	volatile _DWORD _peb_offset_2 = _PEB_Offset_2;
	_DWORD pPeb = _PEB_(_peb_offset_1 + _peb_offset_2);
	volatile _DWORD _ldr_offset_1 = _Ldr_Offset_1;
	volatile _DWORD _ldr_offset_2 = _Ldr_Offset_2;
	_PDWORD pLdr = (_PDWORD) * (_PDWORD)((_DWORD)pPeb + _Ldr_Offset_1 + _Ldr_Offset_2);
	volatile _DWORD _list_offset_1 = _List_Offset_1;
	volatile _DWORD _list_offset_2 = _List_Offset_2;
	_PDWORD InLoadOrderModuleList = (_PDWORD)((_DWORD)pLdr + _list_offset_1 + _list_offset_2);
	_PDWORD pModuleExe = (_PDWORD)*InLoadOrderModuleList;
	_PDWORD pModuleNtdll = (_PDWORD)*pModuleExe;
	_PDWORD pModuleKernel32 = (_PDWORD)*pModuleNtdll;
	dwKernel32 = pModuleKernel32[6];
	return dwKernel32;
}

INLINE _DWORD GetExeBaseAddr() {
	_DWORD dwExe = 0;
	_TEB* pTeb = NtCurrentTeb();
	volatile _DWORD _peb_offset_1 = _PEB_Offset_1;
	volatile _DWORD _peb_offset_2 = _PEB_Offset_2;
	_DWORD pPeb = _PEB_(_peb_offset_1 + _peb_offset_2);
	volatile _DWORD _ldr_offset_1 = _Ldr_Offset_1;
	volatile _DWORD _ldr_offset_2 = _Ldr_Offset_2;
	_PDWORD pLdr = (_PDWORD) * (_PDWORD)((_DWORD)pPeb + _Ldr_Offset_1 + _Ldr_Offset_2);
	volatile _DWORD _list_offset_1 = _List_Offset_1;
	volatile _DWORD _list_offset_2 = _List_Offset_2;
	_PDWORD InLoadOrderModuleList = (_PDWORD)((_DWORD)pLdr + _list_offset_1 + _list_offset_2);
	_PDWORD pModuleExe = (_PDWORD)*InLoadOrderModuleList;
	dwExe = pModuleExe[6];
	return dwExe;
}

INLINE _DWORD GetFuncAddrByHash(_DWORD dwBase, _DWORD hash) {
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)dwBase;
	_PIMAGE_NT_HEADERS pNt = (_PIMAGE_NT_HEADERS)(dwBase + pDos->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)(dwBase + pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	PDWORD pEAT = (PDWORD)(dwBase + pExport->AddressOfFunctions);
	PDWORD pENT = (PDWORD)(dwBase + pExport->AddressOfNames);
	PWORD pEIT = (PWORD)(dwBase + pExport->AddressOfNameOrdinals);
	for (DWORD i = 0; i < pExport->NumberOfNames; i++) {
		char* szFuncName = (char*)(dwBase + pENT[i]);
		if (GetFuncHash(szFuncName) == hash) {
			return dwBase + pEAT[pEIT[i]];
		}
	}
	return 0;
}
