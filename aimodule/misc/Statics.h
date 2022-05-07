#pragma once
#include "misc/Configuration.h"

#include <vector>
#include <string>
#include <sstream>

#include <Windows.h>

#define SPACER(from, size) uint8_t _spacer##from[##size]

namespace statics
{
	static uintptr_t GetGameModuleBaseAddr()
	{
		return (uintptr_t) GetModuleHandle(nullptr);
	}
	
#if defined GAME_AOC
	static uintptr_t TranslateAddr(uintptr_t absoluteAddress, uintptr_t absoluteBaseAddress = aimodule_conf::REFERENCE_BASE_ADDR)
	{
		return GetGameModuleBaseAddr() + (absoluteAddress - absoluteBaseAddress);
	}
#endif

	template<typename T>
	static void SetFuncAddr(T& func, uintptr_t newAddr)
	{
		*reinterpret_cast<uintptr_t*>(&func) = newAddr;
	}

	static std::vector<std::string> SplitString(const std::string& inputString, const char deliminator)
	{
		std::vector<std::string> result;
		std::stringstream stringStream(inputString);
		std::string item;

		while (std::getline(stringStream, item, deliminator))
			result.push_back(item);

		return result;
	}

	static uint8_t HexStringToByte(const std::string& inputString)
	{
		try
		{
			return (uint8_t) std::stoul(inputString, nullptr, 16);
		}
		catch (const std::exception&) { }

		return 0;
	}

	// Get RPC server port
	// Just something that gets the job done right now
	// This doesn't account for all cases, such as quotation marks around the parameter value
	static int GetRpcServerPort()
	{
		std::wstring CmdLine(GetCommandLine());
		std::wstring Keyword = L"-aimoduleport ";
		unsigned int Pos = CmdLine.find(Keyword);

		if (Pos != -1)
		{
			Pos += Keyword.length();
			std::wstring PortString = L"    ";
			while (Pos < CmdLine.length() &&
				((CmdLine[Pos] >= '0' && CmdLine[Pos] <= '9') || CmdLine[Pos] == ' '))
			{
				PortString += CmdLine[Pos++];
			}

			return _wtoi(PortString.c_str());
		}

		return 37412;
	}

	static bool UseDebugConsole()
	{
		std::wstring CmdLine(GetCommandLine());
		std::wstring Keyword = L"-aidebug ";
		unsigned int Pos = CmdLine.find(Keyword);

		return Pos != -1;
	}
}
