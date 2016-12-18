#pragma once
#include <string>
#include <codecvt>

namespace header_only_utils
{
namespace string_utils
{
	std::wstring to_wstring(const std::string& text)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(text);
	}

	std::string to_string(const std::wstring& text)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(text);
	}
}
}