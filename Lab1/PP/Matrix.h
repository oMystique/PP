#pragma once
#include "Definitions.h"

class CMatrix
{
public:
	CMatrix(const Matrix & inputMatrix);
	void CalculateAlgebraicAddition(size_t i, size_t j);
	std::pair<int, int> GetInputMatrixSize()const;
	double CalcMinor(size_t iPos, size_t jPos);

private:
	Matrix m_inputMatrix;
};