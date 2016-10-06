#pragma once
#include "Definitions.h"

class IMatrixCalculator
{
public:
	virtual ~IMatrixCalculator() = default;
	virtual void CalculateMatrixAlgebraicAdds() = 0;
};