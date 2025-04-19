#include "HackProcess.h"


HANDLE CHackProcess::GetGameHandle()
{
	return _GameHandle;
}

HANDLE CHackProcess::Open(DWORD ProcessID)
{
	_GameProcessID = ProcessID;
	_GameHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcessID);
	return _GameHandle;
}
BOOL CHackProcess::Close()
{
	return CloseHandle(_GameHandle);
}

DWORD CHackProcess::GetProcess(const char* processName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 __ProcessEntry;
	__ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	if (hSnapshot == INVALID_HANDLE_VALUE) return 0;
	if (!Process32First(hSnapshot, &__ProcessEntry))
	{
		CloseHandle(hSnapshot);
		return 0;
	}
	do {
		if (!strcmp(__ProcessEntry.szExeFile, processName))
		{
			CloseHandle(hSnapshot);
			Open(__ProcessEntry.th32ProcessID);
			return __ProcessEntry.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &__ProcessEntry));
	CloseHandle(hSnapshot);
	return 0;
}
uintptr_t CHackProcess::GetModuleBaseAddress(const char* processName)
{
	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _GameProcessID);
	if (hSnapShot == INVALID_HANDLE_VALUE)
		return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	if (Module32First(hSnapShot, &lpModuleEntry))
	{
		do
		{
			if (!strcmp(lpModuleEntry.szModule, processName))
			{
				CloseHandle(hSnapShot);
				return (uintptr_t)lpModuleEntry.modBaseAddr;
			}
		} while (Module32First(hSnapShot, &lpModuleEntry));
	}
	CloseHandle(hSnapShot);
	return NULL;
}

bool CHackProcess::LoadLibraryInject(const char* dll)
{
	if (_GameProcessID == NULL)
	{
		return false;
	}

	char customdll[MAX_PATH];
	GetFullPathName(dll, MAX_PATH, customdll, 0);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _GameProcessID);
	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(customdll), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!WriteProcessMemory(hProcess, allocatedMem, customdll, sizeof(customdll), NULL))
		return false;
	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);
	if (hProcess)
		CloseHandle(hProcess);
	return true;
}


/*int CHackProcess::EnableDebugPriv(cchar* name)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	LookupPrivilegeValue(NULL, name, &luid);

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;

	AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
	return 0;

}*/