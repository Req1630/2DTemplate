#ifndef IMAGE_RESOURCE_H
#define IMAGE_RESOURCE_H

#include <Windows.h>
#include <unordered_map>
#include <string>
#include <filesystem>

#include "..\SingletonBase\SingletonBase.h"

namespace fs = std::filesystem;

class CImageResource : tpl::singleton<CImageResource>
{
	const char* IMAGE_FILE_PATH = "Data\\BMP";
public:
	CImageResource();
	virtual ~CImageResource();

	static void Load();
	static void Release();

	static HBITMAP GetBitmap( const std::string& filename );

private:
	std::unordered_map<std::string, HBITMAP> m_BitmapList;
};

#endif	// #ifndef IMAGE_RESOURCE_H.