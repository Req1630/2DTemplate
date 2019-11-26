#ifndef IMAGE_H
#define IMAGE_H

#include <Windows.h>
#include "..\SingletonBase\SingletonBase.h"
#include <string>

//指定色を透過して描画する処理で必要.
#pragma comment ( lib, "msimg32.lib" )

class CImage : public tpl::singleton<CImage>
{
public:
	CImage()
		: m_hScreenDC		( nullptr )
		, m_hMemDC			( nullptr )
		, m_hWorkDC			( nullptr )
		, m_hWorkBMP		( nullptr )
		, m_hmaskBitmapDC	( nullptr )
		, m_hmaskBMP		( nullptr )
	{}

	~CImage()
	{
		DeleteObject( m_hmaskBMP );
		DeleteObject( m_hmaskBitmapDC );
		DeleteObject( m_hWorkBMP );
		DeleteObject( m_hWorkDC );

		m_hScreenDC = nullptr;
		m_hMemDC = nullptr;
	}

	static void Create( HDC hScreenDC, HDC hMemDC );

	// 画像読み込み関数.
	static bool LoadBmp( HBITMAP *hBmp, const char* filename );
	static HBITMAP LoadBmp( const std::string& filename );

	static void SetBitmap( const std::string& filename, HBITMAP hBitmap = nullptr );

	//透過表示.
	static void trnsBlt( 
		const int& x,	// 表示先x座標.
		const int& y,	// 表示先y座標.
		const int& w,	// 表示幅.
		const int& h,	// 表示高さ.
		const int& bx,	// 元画像x座標.
		const int& by );// 元画像y座標.

						//半透明表示.
	static void alphaBlt ( 
		const int& x,			// 表示先x座標.
		const int& y,			// 表示先y座標.
		const int& w,			// 表示幅.
		const int& h,			// 表示高さ.
		const int& bx,			// 元画像x座標.
		const int& by,			// 元画像y座標.
		const int& alpha );		// 透過値(アルファ値).

								// 拡縮表示.
	static void strchBlt(
		const int& x,	// 表示先x座標.
		const int& y,	// 表示先y座標.
		const int& w,	// 表示幅.
		const int& h,	// 表示高さ.
		const int& bx,	// 元画像x座標.
		const int& by,	// 元画像y座標.
		const int& bw,	// 元画像幅.
		const int& bh );// 元画像高さ.

						// 回転表示.
	static void plgBlt(
		const int& cx,			// 表示先 中心x座標.
		const int& cy,			// 表示先 中心y座標.
		const int& bx,			// 元画像x座標.
		const int& by,			// 元画像y座標.
		const int& bw,			// 元画像幅.
		const int& bh,			// 元画像高さ.
		const float& angle );	// 角度.

								// ビット表示.
	static void bitBlt ( 
		const int& x, 		// 表示先x座標.
		const int& y,		// 表示先y座標.
		const int& w,		// 表示幅.
		const int& h,		// 表示高さ.
		const int& bx, 		// 元画像x座標.
		const int& by );	// 元画像y座標.

private:
	void CreatMask( HDC hMemDC, int bx, int by, int sx, int sy );

	HDC m_hScreenDC;
	HDC m_hMemDC;

	HDC		m_hWorkDC;
	HDC		m_hmaskBitmapDC;
	HBITMAP m_hWorkBMP;
	HBITMAP m_hmaskBMP;

	COLORREF oldBkColor;
};

#endif	// #ifndef IMAGE_H.