#pragma once
#include "misc/Configuration.h"

#include <vector>

#include <Windows.h>

#define SPACER(from, size) uint8_t spacer##from[##size]

namespace statics
{
	static uintptr_t GetGameModuleBaseAddr()
	{
		return (uintptr_t) GetModuleHandle(NULL);
	}
	
	static uintptr_t TranslateAddr(uintptr_t absoluteAddress, uintptr_t absoluteBaseAddress = aimodule_conf::REFERENCE_BASE_ADDR)
	{
		return GetGameModuleBaseAddr() + (absoluteAddress - absoluteBaseAddress);
	}

	template<typename T>
	static void SetFuncAddr(T& func, uintptr_t newAddr)
	{
		*reinterpret_cast<uintptr_t*>(&func) = newAddr;
	}
}
