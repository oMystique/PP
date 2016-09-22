#include "MultithreadedMatrixCalculator.h"
#include <boost/optional.hpp>

namespace
{
void GetMatrixWithoutLineAndColumn(const Matrix & mas, Matrix & p, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) 
	{ 
		if (ki == i)
		{
			di = 1;
		}
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) 
		{
			if (kj == j)  dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}

double CalcDetByGausMethod(Matrix & matrix)
{
	size_t i, j, k;
	double det = 1;
	double b = 0;
	for (i = 0; i < matrix.size(); i++)
	{
		for (j = i + 1; j < matrix[0].size(); j++)
		{
			if (matrix[i][i] == 0)
			{
				if (matrix[i][j] == 0)
				{
					b = 0;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				b = matrix[j][i] / matrix[i][i];
			}
			for (k = i; k < matrix.size(); k++)
			{
				matrix[j][k] = matrix[j][k] - matrix[i][k] * b;
			}
		}
		det *= matrix[i][i];
	}
	return det;
}


double CalcMinor(size_t iPos, size_t jPos)
{
	Matrix matrixWithoutIandJ(MATRIX.size() - 1, std::vector<double>(MATRIX.size() - 1));
	GetMatrixWithoutLineAndColumn(MATRIX, matrixWithoutIandJ, iPos, jPos, MATRIX.size());
	auto det = CalcDetByGausMethod(matrixWithoutIandJ);
	return static_cast<double>(std::pow(-1, iPos + jPos + 2)) * (det);
}
}

CMultithreadedMatrixCalculator::CMultithreadedMatrixCalculator(const ThreadsChargeMap & threadsChargeMap)
	: m_threadsChargeMap(threadsChargeMap)
	, m_outputMatrix(Matrix(MATRIX.size(), std::vector<double>(MATRIX.size(), 0)))
{};

const Matrix & CMultithreadedMatrixCalculator::GetOutputMatrix() const
{
	return m_outputMatrix;
}

DWORD CMultithreadedMatrixCalculator::CalculateLine(PVOID pvParam)
{
	auto threadNumber = *static_cast<int*>(pvParam);
	auto linesNumbers = m_threadsChargeMap.at(threadNumber);

	for (auto it = linesNumbers.begin(); it != linesNumbers.end(); ++it)
	{
		for (size_t j = 0; j != MATRIX[0].size(); ++j)
		{
			CalculateAlgebraicAddition(*it, j);
		}
	}
	DWORD dwResult = 0;
	return dwResult;
}

void CMultithreadedMatrixCalculator::CalculateAlgebraicAddition(size_t i, size_t j)
{
	m_outputMatrix[i][j] = CalcMinor(i, j);
}

