#include "ProcessHandler.hpp"

int main(void)
{
	ProcessHandler& gameHandler = ProcessHandler::GetInstance();
	gameHandler.RunProcess();
	return 0;
}