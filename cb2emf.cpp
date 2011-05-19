#define WINVER 0x0400
#define _WIN32_WINNT 0x0400
#define _WIN32_IE 0x0400
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <shlwapi.h>

void PrintError(LPCSTR s)
{
	DWORD writtenBytes;
	WriteFile(GetStdHandle(STD_ERROR_HANDLE), s, strlen(s), &writtenBytes, NULL);
}

bool ClipboardToEmf(LPCTSTR dstFile)
{
	if (HENHMETAFILE hemfSrc = static_cast<HENHMETAFILE>(GetClipboardData(CF_ENHMETAFILE)))
	{
		if (HENHMETAFILE hemf = CopyEnhMetaFile(hemfSrc, dstFile))
		{
			DeleteEnhMetaFile(hemf);
			return true;
		}
		else
		{
			PrintError("Failed to save EMF file.\r\n");
		}
	}
	else
	{
		PrintError("Cannot get EMF from clipboard.\r\n");
	}
	return false;
}

int main()
{
	LPCTSTR args = PathGetArgs(GetCommandLine());

	if (args[0] == TEXT('\0'))
	{
		PrintError("Usage: cb2emf output-filename.emf\r\n");
		return 1;
	}

	OpenClipboard(0);
	bool ret = ClipboardToEmf(args);
	CloseClipboard();

	ExitProcess(ret ? 0 : 1);
}
