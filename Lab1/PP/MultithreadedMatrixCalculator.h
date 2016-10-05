#pragma once
#include "IMatrixCalculator.h"
#include "Matrix.h"

class CMultithreadedMatrixCalculator
	: public IMatrixCalculator
{
public:
	CMultithreadedMatrixCalculator(const CMatrix & matrix, size_t threadsCount);
	const Matrix & CalculateMatrixAlgebraicAdds()override;
	DWORD WINAPI CalculateLine(PVOID pvParam);

private:
	void FillThreadsChargeMap();

private:
	ThreadsChargeMap m_threadsChargeMap;
	CMatrix m_matrix;
	size_t m_threadsCount;
};
