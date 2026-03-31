#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <vector>
#include <Windows.h>

struct ImageData {
	std::vector<BYTE> pixels;
	UINT width;
	UINT height;
	UINT stride; // bytes per row = width * 4
};

class ImageLoader
{
public:
	static bool LoadFromFile(const wchar_t* path, ImageData& data);
};

#endif