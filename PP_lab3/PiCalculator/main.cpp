#include <iostream>
#include "MessageHelper.h"
#include "PiCalculator.h"
#include <chrono>

namespace
{
const int ARGUMENTS_AMOUNT = 3;
bool IsCorrectArgumentsCount(int argc)
{
	return argc == ARGUMENTS_AMOUNT;
}
}

int main(int argc, char* argv[])
{
	if (!IsCorrectArgumentsCount(argc))
	{
		std::cout << "Incorrect arguments count for PiCalculator.exe" << std::endl;
		return EXIT_FAILURE;
	}
	try
	{
		auto iterationsCount = atoi(argv[1]);
		auto processNumber = atoi(argv[2]);
		auto startTime = std::chrono::steady_clock::now();
		auto result = CPiCalculator::CalculatePi(iterationsCount);
		auto endTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = endTime - startTime;

		std::stringstream resultStrm;
		resultStrm << "Iterations count: " << iterationsCount
			<< ", processNumber: " << processNumber
			<< ", result: " << result
			<< ", spent time: " << diff.count();

		header_only_utils::CMessageHelper::SendMessage(resultStrm.str(), L"lab3_pipe");
	}
	catch (std::exception const &exc)
	{
		std::cerr << "PiCalculator.exe was thrown exception: " << exc.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "PiCalculator.exe was thrown exception: " << "Unknow error" << std::endl;
	}

	return EXIT_SUCCESS;
}