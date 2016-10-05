// PP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsistendMatrixCalculator.h"
#include "MultithreadedMatrixCalculator.h"
#include "Matrix_res.h"

int main(int argc, char * argv[])
{
	size_t threadsCount = std::atoi(argv[1]);

	CMatrix matrix(MATRIX);

	auto startTime = std::chrono::steady_clock::now();

	if (threadsCount > 0)
	{
		CMultithreadedMatrixCalculator calc(matrix, threadsCount);
		calc.CalculateMatrixAlgebraicAdds();
	}
	else
	{
		CConsistendMatrixCalculator calc(matrix);
		calc.CalculateMatrixAlgebraicAdds();
	}

	auto endTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = endTime - startTime;

	std::cout << diff.count() << std::endl;

    return 0;
}

