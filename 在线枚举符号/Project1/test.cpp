#include <Windows.h>
#include <stdio.h>
#include <string>
#include <psapi.h>

#include "dbghelp.h"
//#include "imagehlp.h"
#pragma comment(lib,"dbghelp.lib")
#pragma comment(lib, "Imagehlp.lib")
extern "C" {

	PLOADED_IMAGE
		IMAGEAPI
		ImageLoad(
			PCSTR DllName,
			PCSTR DllPath
		);

	BOOL
		IMAGEAPI
		ImageUnload(
			PLOADED_IMAGE LoadedImage
		);

}
BOOL CALLBACK EnumSymCallBack(PSYMBOL_INFO pSymInfo, ULONG SymbolSize, PVOID UserContext)
{
	if (strcmp((pSymInfo->Name), "NtUserSetImeInfoEx") == 0 )
	{
	}
	printf("%-100s :%p\n", pSymInfo->Name, pSymInfo->Address);
	return TRUE;
}

int main()
{
	std::string strMod;
	PVOID dwBaseAddr = 0;
	PVOID pDrvAddr[128 * 8];
	DWORD dwcbNeeded = 0;
	if (EnumDeviceDrivers(pDrvAddr, sizeof(pDrvAddr), &dwcbNeeded))
	{
		for (unsigned int i = 0; i<(dwcbNeeded / 8); i++)
		{
			LPSTR chDrvName[MAX_PATH];
			GetDeviceDriverBaseNameA(pDrvAddr[i], (LPSTR)chDrvName, MAX_PATH);
			dwBaseAddr = pDrvAddr[i];
			strMod = std::string((char*)chDrvName);
			printf("%-20s 0x%p\n", strMod.c_str(), dwBaseAddr);
			break;
		}
	}
	SymSetOptions(SYMOPT_DEFERRED_LOADS);
	HANDLE hProcess = GetCurrentProcess();
	//PLOADED_IMAGE   ploadImage = ImageLoad("win32k.sys", NULL); 
	PLOADED_IMAGE   ploadImage = ImageLoad("win32kbase.sys", NULL);
	SymInitialize(hProcess, 0, FALSE);
	std::string strSymbolPath = "srv*C:\\Windows\\symbols*http://msdl.microsoft.com/download/symbols";
	std::string strSystemPath = "C:\\Windows\\System32\\" + strMod;
	SymSetSearchPath(hProcess, strSymbolPath.c_str());
	HANDLE hSystemFile = CreateFileA(strSystemPath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, 0, NULL);
	DWORD dwFileSize = GetFileSize(hSystemFile, NULL);
	//当前模块
	//DWORD64 dwBase = SymLoadModule64(hProcess, NULL, strSystemPath.c_str(), NULL, (DWORD64)dwBaseAddr, dwFileSize);
	//win32k.sys模块
	DWORD64 dwBase = SymLoadModule64(hProcess, ploadImage->hFile, strSystemPath.c_str(), NULL, (DWORD64)dwBaseAddr, dwFileSize);
	printf("正在枚举符号...\n");
	SymEnumSymbols(hProcess, dwBase, 0, EnumSymCallBack, 0);
	printf("枚举符号结束...\n");
	SymUnloadModule64(hProcess, dwBase);
	SymCleanup(hProcess);
	system("pause");
	return 0;
}