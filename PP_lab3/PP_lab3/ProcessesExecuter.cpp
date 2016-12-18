#include "stdafx.h"
#include "ProcessesExecuter.h"
#include "MessageHelper.h"

namespace
{
const wchar_t CALCULATOR_EXE_NAME[] = L"PiCalculator.exe";
struct SProcessData
{
	SProcessData(STARTUPINFO startupInfo, PROCESS_INFORMATION processInfo, HANDLE handle)
		: startupInfo(startupInfo)
		, processInfo(processInfo)
		, handle(handle)
	{};
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;
	HANDLE handle;
};
}

struct CProcessesExecuter::Impl
{
public:
	void RunProcesses(int processesCount, int iterationsCount)
	{
		m_processesCount = processesCount;
		for (int i = 0; i != processesCount; ++i)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			ZeroMemory(&pi, sizeof(pi));
			std::wstringstream commandStrm;
			commandStrm << CALCULATOR_EXE_NAME << L" " << iterationsCount << L" " << i;
			si.dwFlags = STARTF_USESIZE | STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_SHOW;
			if (!CreateProcess(NULL, LPWSTR(commandStrm.str().c_str()), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL , &si , &pi))
			{
				throw std::invalid_argument("Do not create a process.");
			}
			m_processesData.push_back(SProcessData(si, pi, pi.hThread));
		}
		header_only_utils::CMessageHelper::WaitMessages(m_messages, m_processesCount, L"lab3_pipe");
		CloseProcessesHandles();
	}

	std::vector<std::string> GetProcessesMessages()const
	{
		return m_messages;
	}

	void CloseProcessesHandles()
	{
		for (size_t i = 0; i != m_processesCount; i++)
		{
			CloseHandle(m_processesData[i].processInfo.hProcess);
			CloseHandle(m_processesData[i].processInfo.hThread);
		}
	}

private:
	size_t m_processesCount;
	std::vector<SProcessData> m_processesData;
	std::vector<std::string> m_messages;
};

CProcessesExecuter::CProcessesExecuter()
	: m_pImpl(std::make_unique<Impl>())
{
}

CProcessesExecuter::~CProcessesExecuter()
{
}

void CProcessesExecuter::RunProcesses(int processesCount, int iterationsCount)
{
	m_pImpl->RunProcesses(processesCount, iterationsCount);
}

std::vector<std::string> CProcessesExecuter::GetProcessesMessages()const
{
	return m_pImpl->GetProcessesMessages();
}