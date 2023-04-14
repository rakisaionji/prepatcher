#pragma once
#include <Windows.h>

namespace Patch
{
	struct PatchData
	{
		#ifdef WIN32
			DWORD Address;
		#else
			DWORD64 Address;
		#endif
		
		DWORD Length;
		BYTE* OriginalBytes;
		BYTE* PatchedBytes;

		PatchData();
		~PatchData();
	};
}
