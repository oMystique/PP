#pragma once
#include "NamedPipe.h"
#include <vector>

namespace header_only_utils
{
class CMessageHelper
{
	CMessageHelper() = delete;
	CMessageHelper & operator=(CMessageHelper const&) = delete;
	CMessageHelper & operator=(CMessageHelper &&) = delete;
public:
	static void SendMessage(std::string const &message, const std::wstring & pipeName)
	{
		auto pipePath = L"\\\\.\\Pipe\\" + pipeName;
		CPipe pipe;
		pipe.Open(pipePath);
		pipe.WriteInfo(message.data(), message.size());
		pipe.Close();
	}

	static void WaitMessages(std::vector<std::string> &messages, size_t amountMessages, const std::wstring & pipeName)
	{
		auto pipePath = L"\\\\.\\Pipe\\" + pipeName;
		CNamedPipe pipe;
		pipe.Open(pipePath);
		for (size_t index = 0; index < amountMessages; ++index)
		{
			char buffer[BUFFER_PIPE_SIZE] = "";
			pipe.ReadInfo(buffer, BUFFER_PIPE_SIZE);
			messages.push_back(buffer);
		}
		pipe.Close();
	}
};
}