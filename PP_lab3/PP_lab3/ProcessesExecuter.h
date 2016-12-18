#pragma once
#include <memory>

class CProcessesExecuter
{
	struct Impl;
public:
	CProcessesExecuter();
	~CProcessesExecuter();
	void RunProcesses(int processesCount, int iterationsCount);
	std::vector<std::string> GetProcessesMessages()const;

private:
	std::unique_ptr<Impl> m_pImpl;
};