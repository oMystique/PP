// PP_lab3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ProcessesExecuter.h"

namespace
{
const int MIN_ARGUMENTS_COUNT = 2;
const int MAX_ARGUMENTS_COUNT = 3;
const char HELP_FLAG[] = "/?";
void PrintHelp()
{
	std::cout << "***Help:" << std::endl;
	std::cout << "PP_lab3.exe <processes count> <iterations count>" << std::endl;
	std::cout << "PP_lab3.exe /? - to print help" << std::endl;
	std::cout << "***" << std::endl;
}
bool IsIncorrectArgumentsCount(int argc)
{
	return argc < MIN_ARGUMENTS_COUNT || argc > MAX_ARGUMENTS_COUNT;
}
}

int main(int argc, char*argv[])
{
	if (IsIncorrectArgumentsCount(argc))
	{
		std::cout << "Incorrect arguments count. Usage /? flag to get help." << std::endl;
		return EXIT_FAILURE;
	}

	if (argc == MIN_ARGUMENTS_COUNT)
	{
		if (argv[1] != HELP_FLAG)
		{
			std::cout << "Incorrect help flag. Usage /? to get help." << std::endl;
			return EXIT_FAILURE;
		}
		else
		{
			PrintHelp();
			return EXIT_SUCCESS;
		}
	}
	try
	{
		CProcessesExecuter executer;
		executer.RunProcesses(atoi(argv[1]), atoi(argv[2]));
		for (auto const & message : executer.GetProcessesMessages())
		{
			std::cout << message.c_str() << std::endl;
		}
	}
	catch (std::exception const &exc)
	{
		std::cerr << "PP_lab3.exe was thrown exception: " << exc.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "PP_lab3.exe was thrown exception: " << "Unknow error" << std::endl;
	}

    return EXIT_SUCCESS;
}

