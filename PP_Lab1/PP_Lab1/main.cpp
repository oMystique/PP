#include <chrono>
#include <iostream>
#include "MultithreadedCalculatorHelper.h"
#include <memory>

using namespace std;

void PrintMatrix(const Matrix & matrix)
{
	for (size_t i = 0; i != MATRIX.size(); ++i)
	{
		for (size_t j = 0; j != MATRIX[0].size(); ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

ThreadsChargeMap FillThreadsChargeMap(size_t threadsCount)
{
	map<size_t, vector<size_t>> threadsChargeMap;
	for (size_t i = 1; i <= threadsCount; i++)
	{
		threadsChargeMap.emplace(i, vector<size_t>());
	}
	for (size_t i = 0, threadNumber = 1; i != MATRIX.size(); i++, threadNumber++)
	{
		if (threadNumber > threadsCount)
		{
			threadNumber = 1;
		}
		threadsChargeMap.at(threadNumber).push_back(i);
	}

	return threadsChargeMap;
}

int main(int argc, char * argv[]) //TODO: выделить класс MatrixUtils; Ликвидировать из main() лишний код, связанный с созданием потков
{
	const size_t threadsCount = argc == 1 ? 1 : atoi(argv[1]);

	CMultithreadedMatrixCalculator calc(FillThreadsChargeMap(threadsCount));

	auto startTime = chrono::steady_clock::now();

	HANDLE *hThreads = *make_shared<HANDLE*>(new HANDLE[threadsCount]);
	DWORD *dwThreadsId = *make_shared<DWORD*>(new DWORD[threadsCount]);

	for (size_t i = 1; i < threadsCount; i++)
	{
		SMultithreadedCalculatorHelper helper(i, calc);
		hThreads[i - 1] = CreateThread(NULL, 0, StartMultithreadedCalculator, (PVOID)&helper, 0, &dwThreadsId[i - 1]);
	}

	calc.CalculateLine((PVOID)&threadsCount);
	WaitForMultipleObjects(threadsCount - 1, hThreads, TRUE, INFINITE);

	auto endTime = chrono::steady_clock::now();
	chrono::duration<double> diff = endTime - startTime;

	cout << diff.count() << endl;



	return 0;
}

