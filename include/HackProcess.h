#pragma once

#include <Windows.h>
#include <TlHelp32.h>
//THIS FILE SIMPLY DOES MOST OF THE BACKEND WORK FOR US,
//FROM FINDING THE PROCESS TO SETTING UP CORRECT ACCESS FOR US
//TO EDIT MEMORY
//IN MOST GAMES, A SIMPLER VERSION OF THIS CAN BE USED, or if you're injecting then its often not necessary
//This file has been online for quite a while so credits should be shared but im using this from NubTIK
//So Credits to him and thanks





class CHackProcess
{
private:
	HANDLE		_GameHandle;
	DWORD		_GameProcessID;

public:
	HANDLE Open(DWORD ProcessID);
	BOOL Close();
	HANDLE GetGameHandle();
	DWORD GetProcess(const char* processName);
	uintptr_t GetModuleBaseAddress(const char* processName);
	bool LoadLibraryInject(const char* dll);
	//int EnableDebugPriv(const char* name);
};













