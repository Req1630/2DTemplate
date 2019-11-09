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
	const char* IMAGE_FILE_PATH = "Data\\Image";
public:
	CImageResource();
	virtual ~CImageResource();

	static void Load( HDC hMemDC );
	static void Release();

	static bool SetBitmap( const std::string& filename );

private:
	std::unordered_map<std::string, HBITMAP> m_BitmapList;
	HDC m_hMemDC;
};

#endif	// #ifndef IMAGE_RESOURCE_H.