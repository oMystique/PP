#pragma once
#include <string>
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <assert.h>
#include <sstream>

static const size_t BUFFER_PIPE_SIZE = 512;

namespace header_only_utils
{
class IPipe
{
public:
	virtual ~IPipe() = default;
	virtual void ReadInfo(void* buffer, size_t size) = 0;
	virtual void WriteInfo(const void* buffer, size_t size) = 0;
	virtual void Open(const std::wstring& name) = 0;
	virtual void Close() = 0;
};
};