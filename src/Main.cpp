#include "Patch/Patcher.h"

#ifdef WIN32
const DWORD PLATFORM_TYPE = 32;
#else
const DWORD PLATFORM_TYPE = 64;
#endif

int GetDirectorySeperatorPosition(std::string path)
{
	for (int i = path.size() - 1; i >= 0; i--)
	{
		auto currentChar = path[i];
		if (currentChar == '\\' || currentChar == '/')
			return i;
	}

	return -1;
}

/*
std::string GetModuleDirectory()
{
	HMODULE module = GetModuleHandleW(NULL);
	CHAR modulePathBuffer[MAX_PATH];
	GetModuleFileName(module, modulePathBuffer, MAX_PATH);

	auto modulePath = std::string(modulePathBuffer);
	int seperatorPos = GetDirectorySeperatorPosition(modulePath);

	if (seperatorPos != -1)
		return std::string(modulePathBuffer).substr(0, seperatorPos);

	return NULL;
}
*/

std::string GetFileName(std::string const& path)
{
	return path.substr(path.find_last_of("/\\") + 1);
}

bool DoesFileExist(std::string filePath)
{
	auto fileAttrib = GetFileAttributes(filePath.c_str());
	return fileAttrib != INVALID_FILE_ATTRIBUTES;
}

int main(int argc, char** argv)
{
	printf("main(): Running in %d-bit mode...\n", PLATFORM_TYPE);

	if (argc < 2)
	{
		printf("main(): Insufficient number of arguments supplied\n");
		printf("main(): Please read the instructions carefully");
		printf("main(): Press enter to exit...");
		std::cin.get();
		return EXIT_FAILURE;
	}

	// === Param 1: Patch Executable ===

	auto targetFilePath = std::string(argv[1]);
	auto targetFileName = GetFileName(targetFilePath);

	printf("main(): Checking target file location...\n");

	if (!DoesFileExist(targetFilePath))
	{
		printf("main(): Unable to locate %s\n", targetFileName.c_str());
		printf("main(): Press enter to exit...\n");
		std::cin.get();
		return EXIT_FAILURE;
	}
	else
	{
		printf("main(): %s successfully located\n", targetFileName.c_str());
	}

	// === Param 2: Patch Definition File ===

	auto patchFilePath = (argc < 3) ? "patch.txt" : std::string(argv[2]);
	auto patchFileName = GetFileName(patchFilePath);

	printf("main(): Checking patch file location...\n");

	if (!DoesFileExist(patchFilePath))
	{
		printf("main(): Unable to locate %s\n", patchFileName.c_str());
		printf("main(): Press enter to exit...");
		std::cin.get();
		return EXIT_FAILURE;
	}
	else
	{
		printf("main(): %s successfully located\n", patchFileName.c_str());
	}

	printf("main(): Patching target file %s...\n", targetFileName.c_str());

	Patch::Patcher patcher;
	patcher.LoadPatchFile(patchFilePath);
	patcher.PatchProgram(targetFilePath);

	printf("main(): Press enter to exit...");
	std::cin.get();
	return EXIT_SUCCESS;
}
