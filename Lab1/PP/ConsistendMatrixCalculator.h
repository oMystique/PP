#pragma once
#include "IMatrixCalculator.h"
#include "Matrix.h"

class CConsistendMatrixCalculator
	: public IMatrixCalculator
{
public:
	CConsistendMatrixCalculator(const CMatrix & matrix);
	const Matrix & CalculateMatrixAlgebraicAdds() override;

private:
	CMatrix m_matrix;
};
