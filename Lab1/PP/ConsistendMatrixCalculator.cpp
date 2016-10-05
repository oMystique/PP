#include "stdafx.h"
#include "ConsistendMatrixCalculator.h"

CConsistendMatrixCalculator::CConsistendMatrixCalculator(const CMatrix & matrix)
	: m_matrix(matrix)
{
}

const Matrix & CConsistendMatrixCalculator::CalculateMatrixAlgebraicAdds()
{
	auto matrixSize = m_matrix.GetInputMatrixSize();
	for (size_t i = 0; i != matrixSize.first; i++)
	{
		for (size_t j = 0; j != matrixSize.second; j++)
		{
			m_matrix.CalculateAlgebraicAddition(i, j);
		}
	}
	return m_matrix.GetOutputMatrix();
}
