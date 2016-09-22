#pragma once
#include "MultithreadedMatrixCalculator.h"

struct SMultithreadedCalculatorHelper
{
	SMultithreadedCalculatorHelper(int threadNumber, CMultithreadedMatrixCalculator & matrixCalc)
		: threadNumber(threadNumber)
		, matrixCalc(matrixCalc)
	{};
	int threadNumber;
	CMultithreadedMatrixCalculator & matrixCalc;
};

DWORD WINAPI StartMultithreadedCalculator(PVOID pvParam)
{
	auto helper = static_cast<SMultithreadedCalculatorHelper*>(pvParam);
	return helper->matrixCalc.CalculateLine((PVOID)&helper->threadNumber);
}