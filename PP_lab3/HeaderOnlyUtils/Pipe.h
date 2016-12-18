#pragma once
#include "IPipe.h"
#include "StringUtils.h"

namespace header_only_utils
{
class CPipe
	: public IPipe
{
public:
	void ReadInfo(void* buffer, size_t size) override
	{
		DWORD dwRead;
		BOOL bSuccess = ReadFile(m_hPipe, buffer, DWORD(size), &dwRead, NULL);
		if (!bSuccess || (dwRead == 0))
		{
			throw std::runtime_error("Read error");
		}
	}

	void WriteInfo(const void* buffer, size_t size) override
	{
		DWORD dwWritten;
		if (!WriteFile(m_hPipe, buffer, DWORD(size), &dwWritten, NULL))
		{
			throw std::runtime_error("Write error");
		}
	}

	void Open(const std::wstring& name) override
	{
		m_name = name;
		m_hPipe = CreateFile(LPCWSTR(name.c_str()), GENERIC_ALL, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (m_hPipe == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("Error for open pipe " + string_utils::to_string(m_name));
		}
	}

	void Close() override
	{
		CloseHandle(m_hPipe);
		m_hPipe = nullptr;
	}

protected:
	std::wstring m_name;
	HANDLE m_hPipe;
};
}