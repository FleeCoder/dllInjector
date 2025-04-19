#pragma once
#include <Windows.h>
#include "HackProcess.h"
#include <string>

class ProcessHandler
{
private:
	DWORD _dwordGameHandler;
	CHackProcess _hackProcess;
	PROCESSENTRY32* _gameProccess;
	const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz1234567890";

private:
	ProcessHandler();
	void CleanUp();
	std::string& RandomStringGen(const size_t length);

public:
	ProcessHandler(ProcessHandler&) = delete;
	void operator=(const ProcessHandler&) = delete;

	static ProcessHandler& GetInstance();
	HANDLE GetGameHandler();
	DWORD GetGameBase();
	void RunProcess();
	bool DoesLoaderExist(const char* name);
};

