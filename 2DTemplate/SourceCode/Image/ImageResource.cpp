#include "ImageResource.h"
#include "Image.h"
#include <crtdbg.h>

CImageResource::CImageResource()
{
}

CImageResource::~CImageResource()
{
}

void CImageResource::Load()
{
	auto image_search = [&]( const fs::directory_entry& entry )
	{
		std::string extension = entry.path().extension().string();
		std::string filepath = entry.path().string();
		std::string filename = entry.path().stem().string();

		if( extension != ".bmp" && extension != ".BMP" ) return;
		
		GetInstance()->m_BitmapList[filename] = CImage::LoadBmp( filepath.c_str() );
	};
	try {
		fs::recursive_directory_iterator dir_it(GetInstance()->IMAGE_FILE_PATH), end_it;
		std::for_each(dir_it, end_it, image_search );

	} catch( fs::filesystem_error& e ){
		std::string Message = e.what();
		_ASSERT_EXPR(false, L"ディレクトリ取得失敗");
	}
}

void CImageResource::Release()
{
	for( auto& m : GetInstance()->m_BitmapList ){
		DeleteObject( m.second );
		m.second = nullptr;
	}
}

HBITMAP CImageResource::GetBitmap( const std::string& filename )
{
	auto itr = GetInstance()->m_BitmapList.find(filename);
	if( itr != GetInstance()->m_BitmapList.end() ){
		return itr->second;
	} else {
		_ASSERT_EXPR( false, L"BITMAPが見つかりません" );
	}
	return nullptr;
}