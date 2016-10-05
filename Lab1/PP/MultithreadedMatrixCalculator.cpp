#include "stdafx.h"
#include "MultithreadedMatrixCalculator.h"

namespace
{
DWORD WINAPI StartMultithreadedCalculator(PVOID pvParam)
{
	auto data = static_cast<std::pair<CMultithreadedMatrixCalculator*, int>*>(pvParam);
	return data->first->CalculateLine((PVOID)&data->second);
}
}

CMultithreadedMatrixCalculator::CMultithreadedMatrixCalculator(const CMatrix & matrix, size_t threadsCount)
	: m_matrix(matrix)
	, m_threadsCount(threadsCount)
{	
	FillThreadsChargeMap();
}

const Matrix & CMultithreadedMatrixCalculator::CalculateMatrixAlgebraicAdds()
{
	HANDLE *hThreads = *std::make_shared<HANDLE*>(new HANDLE[m_threadsCount]);
	DWORD *dwThreadsId = *std::make_shared<DWORD*>(new DWORD[m_threadsCount]);

	for (size_t i = 1; i <= m_threadsCount; i++)
	{
		hThreads[i - 1] = CreateThread(NULL, 0, StartMultithreadedCalculator, (PVOID)&(std::make_pair(this, i)), 0, &dwThreadsId[i - 1]);
	}

	WaitForMultipleObjects(m_threadsCount, hThreads, TRUE, INFINITE);

	return m_matrix.GetOutputMatrix();
}

void CMultithreadedMatrixCalculator::FillThreadsChargeMap()
{
	auto const & matrixSize = m_matrix.GetInputMatrixSize();
	for (size_t i = 1; i <= m_threadsCount; i++)
	{
		m_threadsChargeMap.emplace(i, std::vector<size_t>());
	}
	for (size_t i = 0, threadNumber = 1; i != matrixSize.first; i++, threadNumber++)
	{
		if (threadNumber > m_threadsCount)
		{
			threadNumber = 1;
		}
		m_threadsChargeMap.at(threadNumber).push_back(i);
	}
}

DWORD CMultithreadedMatrixCalculator::CalculateLine(PVOID pvParam)
{
	auto threadNumber = *static_cast<int*>(pvParam);
	auto linesNumbers = m_threadsChargeMap.at(threadNumber);

	for (auto it = linesNumbers.begin(); it != linesNumbers.end(); ++it)
	{
		for (size_t j = 0; j != m_matrix.GetInputMatrixSize().first; ++j)
		{
			m_matrix.CalculateAlgebraicAddition(*it, j);
		}
	}

	DWORD dwResult = 0;
	return dwResult;
}
