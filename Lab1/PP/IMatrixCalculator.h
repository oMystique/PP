#pragma once
#include "Definitions.h"

class IMatrixCalculator
{
public:
	virtual ~IMatrixCalculator() = default;
	virtual const Matrix & CalculateMatrixAlgebraicAdds() = 0;
};