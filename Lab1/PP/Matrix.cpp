#include "stdafx.h"
#include "Matrix.h"

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
}

CMatrix::CMatrix(const Matrix & inputMatrix)
	: m_inputMatrix(inputMatrix)
{
}

void CMatrix::CalculateAlgebraicAddition(size_t i, size_t j)
{
	CalcMinor(i, j);
}

std::pair<int, int> CMatrix::GetInputMatrixSize() const
{
	return{ m_inputMatrix.size(), m_inputMatrix[0].size() };
}

double CMatrix::CalcMinor(size_t iPos, size_t jPos)
{
	auto matrixSize = m_inputMatrix.size();
	Matrix matrixWithoutIandJ(matrixSize - 1, std::vector<double>(matrixSize - 1));
	GetMatrixWithoutLineAndColumn(m_inputMatrix, matrixWithoutIandJ, iPos, jPos, matrixSize);
	auto det = CalcDetByGausMethod(matrixWithoutIandJ);
	return static_cast<double>(std::pow(-1, iPos + jPos + 2)) * (det);
}
