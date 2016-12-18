#pragma once
#include "Pipe.h"
#include "StringUtils.h"

namespace header_only_utils
{
class CNamedPipe :
	public CPipe
{
public:
	void ReadInfo(void* buffer, size_t size) override
	{
		if (ConnectNamedPipe(m_hPipe, NULL))
		{
			DWORD dwRead;
			if (!ReadFile(m_hPipe, buffer, DWORD(size), &dwRead, NULL) || (dwRead == NULL))
			{
				throw std::runtime_error("Read pipe error.");
			}
		}
		DisconnectNamedPipe(m_hPipe);
	}

	void WriteInfo(const void* buffer, size_t size) override
	{
		if (ConnectNamedPipe(m_hPipe, NULL))
		{
			DWORD dwWritten;
			if (!WriteFile(m_hPipe, buffer, DWORD(size), &dwWritten, NULL))
			{
				throw std::runtime_error("Write pipe error.");
			}
		}
		DisconnectNamedPipe(m_hPipe);
	}

	void Open(const std::wstring& name) override
	{
		m_name = name;
		m_hPipe = CreateNamedPipe(
			(LPWSTR)m_name.data(),
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUFFER_PIPE_SIZE,
			BUFFER_PIPE_SIZE,
			NULL,
			NULL
		);
		if (m_hPipe == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("Error for open pipe " + string_utils::to_string(m_name));
		}
	}

	void Close() override
	{
		DisconnectNamedPipe(m_hPipe);
		CloseHandle(m_hPipe);
		m_hPipe = nullptr;
	}
};
}