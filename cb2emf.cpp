#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc <= 1)
	{
		std::cerr << "�t�@�C�������w�肵�Ă��������B" << std::endl;
		return 1;
	}

	OpenClipboard(0);

	auto hemfSrc = static_cast<HENHMETAFILE>(GetClipboardData(CF_ENHMETAFILE));
	auto hemf = CopyEnhMetaFile(hemfSrc, argv[1]);
	DeleteEnhMetaFile(hemf);

	CloseClipboard();
	return 0;
}

