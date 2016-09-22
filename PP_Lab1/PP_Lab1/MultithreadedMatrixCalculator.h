#include "matrix_res.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

class CMultithreadedMatrixCalculator
{
public:
	CMultithreadedMatrixCalculator(const ThreadsChargeMap & threadsChargeMap);

	const Matrix & GetOutputMatrix()const;
	DWORD WINAPI CalculateLine(PVOID pvParam);

private:
	void CalculateAlgebraicAddition(size_t i, size_t j);

private:
	ThreadsChargeMap m_threadsChargeMap;
	Matrix m_outputMatrix;
};
