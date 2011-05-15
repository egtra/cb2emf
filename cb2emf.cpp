#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc <= 1)
	{
		std::cerr << "Usage: cb2emf output-filename.emf" << std::endl;
		return 1;
	}

	OpenClipboard(0);

	if (auto hemfSrc = static_cast<HENHMETAFILE>(GetClipboardData(CF_ENHMETAFILE)))
	{
		auto hemf = CopyEnhMetaFile(hemfSrc, argv[1]);
		DeleteEnhMetaFile(hemf);
	}
	else
	{
		std::cerr << "Cannot get EMF from clipboard." << std::endl;
	}
	CloseClipboard();
	return 0;
}

