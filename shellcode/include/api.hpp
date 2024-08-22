#pragma once
typedef HMODULE(WINAPI* LoadLibraryAFunc)(_In_ LPCSTR lpLibFileName);
typedef UINT(WINAPI* WinExecFunc)(_In_ LPCSTR lpCmdLine, _In_ UINT uCmdShow);
typedef int (WINAPI* MessageBoxAFunc)(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType);
typedef int (WINAPI* MessageBoxWFunc)(_In_opt_ HWND hWnd, _In_opt_ LPCWSTR lpText, _In_opt_ LPCWSTR lpCaption, _In_ UINT uType);
typedef DWORD(WINAPI* GetFileAttributesAFunc)(_In_ LPCSTR lpFileName);
typedef VOID(WINAPI* ExitProcessFunc)(_In_ UINT uExitCode);
typedef HANDLE(WINAPI* CreateFileAFunc)(_In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);
typedef DWORD(WINAPI* GetFileSizeFunc)(_In_ HANDLE hFile, _Out_opt_ LPDWORD lpFileSizeHigh);
typedef LPVOID(WINAPI* VirtualAllocFunc)(_In_opt_ LPVOID lpAddress, _In_     SIZE_T dwSize, _In_     DWORD flAllocationType, _In_     DWORD flProtect);
typedef BOOL(WINAPI* ReadFileFunc)(_In_ HANDLE hFile, _Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer, _In_ DWORD nNumberOfBytesToRead, _Out_opt_ LPDWORD lpNumberOfBytesRead, _Inout_opt_ LPOVERLAPPED lpOverlapped);
typedef BOOL(WINAPI* VirtualProtectFunc)(_In_  LPVOID lpAddress, _In_  SIZE_T dwSize, _In_  DWORD flNewProtect, _Out_ PDWORD lpflOldProtect);
typedef HANDLE(WINAPI* GetStdHandleFunc)(_In_ DWORD nStdHandle);
typedef BOOL(WINAPI* WriteConsoleAFunc)(_In_ HANDLE hConsoleOutput, _In_reads_(nNumberOfCharsToWrite) CONST VOID* lpBuffer, _In_ DWORD nNumberOfCharsToWrite, _Out_opt_ LPDWORD lpNumberOfCharsWritten, _Reserved_ LPVOID lpReserved);
typedef VOID(WINAPI* SleepFunc)(_In_ DWORD dwMilliseconds);
typedef HWND(APIENTRY* GetConsoleWindowFunc)(VOID);

constexpr DWORD Hash(const char* functionName) {
	DWORD hash = 0;
	while (*functionName) {
		hash = (hash * 138) + *functionName;
		functionName++;
	}
	return hash;
}

constexpr auto LoadLibraryAHash = Hash("LoadLibraryA");
constexpr auto WinExecHash = Hash("WinExec");
constexpr auto MessageBoxAHash = Hash("MessageBoxA");
constexpr auto MessageBoxWHash = Hash("MessageBoxW");
constexpr auto GetFileAttributesAHash = Hash("GetFileAttributesA");
constexpr auto ExitProcessHash = Hash("ExitProcess");
constexpr auto CreateFileAHash = Hash("CreateFileA");
constexpr auto GetFileSizeHash = Hash("GetFileSize");
constexpr auto VirtualAllocHash = Hash("VirtualAlloc");
constexpr auto ReadFileHash = Hash("ReadFile");
constexpr auto VirtualProtectHash = Hash("VirtualProtect");
constexpr auto GetStdHandleHash = Hash("GetStdHandle");
constexpr auto WriteConsoleAHash = Hash("WriteConsoleA");
constexpr auto SleepHash = Hash("Sleep");
constexpr auto GetConsoleWindowHash = Hash("GetConsoleWindow");

typedef struct _FUNCTION {
	_DWORD dwDllBase;
	DWORD* funcHashs;
	DWORD count;
}Function;