#include "ProcessHandler.hpp"
#include "ProcessHandler_Cfg.hpp"
#include <iostream>

ProcessHandler::ProcessHandler(): _gameProccess(nullptr)
{

}

ProcessHandler& ProcessHandler::GetInstance()
{
	static ProcessHandler processHandler;
	return processHandler;
}

DWORD ProcessHandler::GetGameBase()
{
	return _dwordGameHandler;
}

HANDLE ProcessHandler::GetGameHandler()
{
	return _hackProcess.GetGameHandle();
}

void ProcessHandler::RunProcess()
{
	std::cout << "process started!!!" << std::endl;
	SetConsoleTitleA(RandomStringGen(26).c_str());
	if (!_hackProcess.GetProcess(gameProcessName))
	{
		CleanUp();
	}
	uintptr_t moduleBase = _hackProcess.GetModuleBaseAddress(gameProcessName);
	if (moduleBase == NULL)
	{
		CleanUp();
	}
	if (DoesLoaderExist(dllFileName))
	{
		if (_hackProcess.LoadLibraryInject(dllFileName))
		{
			std::cout << "Library Injected successfuly to the process!!!" << std::endl;
			CleanUp();
		}
		else
		{
			std::cout << "failed to inject Library to the Game process !!!    :(";
			CleanUp();
		}
	}
	std::cout << "process ended!!!" << std::endl;
}

void ProcessHandler::CleanUp()
{
	system("pause");
	ExitProcess(0);
}

std::string& ProcessHandler::RandomStringGen(const size_t length)
{
	std::string randString;
	srand((unsigned)time(NULL) * 5);
	for (int i = 0;i < length;i++)
		randString += characters[rand()%(characters.size()-1)];
	return randString;
}

bool ProcessHandler::DoesLoaderExist(const char* filePath)
{
	if (FILE* file = fopen(filePath, "r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}