#include "Image.h"
#include "ImageResource.h"
#include "..\Global.h"

void CImage::Create( HDC hScreenDC, HDC hMemDC )
{
	GetInstance()->m_hScreenDC = hScreenDC;
	GetInstance()->m_hMemDC = hMemDC;
	GetInstance()->m_hWorkDC = CreateCompatibleDC ( hScreenDC );//作業用DC作成.
	GetInstance()->m_hWorkBMP = CreateCompatibleBitmap (hScreenDC, WND_W*2, WND_H*2 );//作業用ビットマップ作成.
	SelectObject ( GetInstance()->m_hWorkDC, GetInstance()->m_hWorkBMP );	//DCとビットマップの関連付け.
}

bool CImage::LoadBmp( HBITMAP *hBmp, const char* filename )
{
	//背景の読み込み.
	*hBmp = ( HBITMAP ) LoadImage (
		NULL,				//インスタンス番号(省略).
		filename,			//ファイル名.
		IMAGE_BITMAP,		//ビットマップ形式.
		0, 0,				//読み込む画像のx, y座標.
		LR_LOADFROMFILE );	//ファイルから読み込む.
	if ( *hBmp == NULL ) {
		MessageBox ( NULL,
			"画像ファイルの読み込み失敗",
			filename, MB_OK );
		return false;
	}
	return true;
}

HBITMAP CImage::LoadBmp( const std::string& filename )
{
	try {
		return (HBITMAP)LoadImage(
			NULL,				//インスタンス番号(省略).
			filename.c_str(),			//ファイル名.
			IMAGE_BITMAP,		//ビットマップ形式.
			0, 0,				//読み込む画像のx, y座標.
			LR_LOADFROMFILE);	//ファイルから読み込む.
	} catch ( const std::exception& ) {
		MessageBox(NULL,
			"画像ファイルの読み込み失敗",
			filename.c_str(), MB_OK);
	}

}

void CImage::SetBitmap( const std::string& filename, HBITMAP hBitmap )
{
	const HBITMAP bmp = hBitmap == nullptr 
		? CImageResource::GetBitmap(filename) : hBitmap;
	SelectObject( GetInstance()->m_hMemDC, bmp );
}

//透過表示.
void CImage::trnsBlt(
	const int& x,	// 表示先x座標.
	const int& y,	// 表示先y座標.
	const int& w,	// 表示幅.
	const int& h,	// 表示高さ.
	const int& bx,	// 元画像x座標.
	const int& by)	// 元画像y座標.
{
	TransparentBlt (
		GetInstance()->m_hScreenDC,
		x, y,					
		w, h,					
		GetInstance()->m_hMemDC,
		bx, by,					
		w, h,					
		RGB ( 0x00, 0xFF, 0x00 ));
}

//半透明表示.
void CImage::alphaBlt(
	const int& x,			// 表示先x座標.
	const int& y,			// 表示先y座標.
	const int& w,			// 表示幅.
	const int& h,			// 表示高さ.
	const int& bx,			// 元画像x座標.
	const int& by,			// 元画像y座標.
	const int& alpha )		// 透過値(アルファ値).
{
	//透過構造体.
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, (BYTE)0, (BYTE)alpha, (BYTE)0 };

	BitBlt (
		GetInstance()->m_hWorkDC,
		WND_W, WND_H,
		w, h,
		GetInstance()->m_hScreenDC,
		x, y,
		SRCCOPY );

	TransparentBlt(
		GetInstance()->m_hWorkDC,
		WND_W, WND_H,
		w, h,
		GetInstance()->m_hMemDC,
		bx, by,
		w, h,
		RGB(0x00, 0xFF, 0x00));

	AlphaBlend ( 
		GetInstance()->m_hScreenDC,
		x, y,
		w, h,
		GetInstance()->m_hWorkDC,
		WND_W, WND_H,
		w, h,
		blendfunc );
}

void CImage::strchBlt(
	const int& x,	// 表示先x座標.
	const int& y,	// 表示先y座標.
	const int& w,	// 表示幅.
	const int& h,	// 表示高さ.
	const int& bx,	// 元画像x座標.
	const int& by,	// 元画像y座標.
	const int& bw,	// 元画像幅.
	const int& bh )	// 元画像高さ.
{
	StretchBlt(
		GetInstance()->m_hWorkDC,
		WND_W, 0,	
		w, h,		
		GetInstance()->m_hMemDC,
		bx, by,		
		bw, bh,		
		SRCAND );
	TransparentBlt(
		GetInstance()->m_hScreenDC,
		x, y,
		w, h,
		GetInstance()->m_hWorkDC,
		WND_W, 0,
		w, h,
		RGB(0x00, 0xFF, 0x00));
}

void CImage::plgBlt(
	const int& cx,			// 表示先 中心x座標.
	const int& cy,			// 表示先 中心y座標.
	const int& bx,			// 元画像x座標.
	const int& by,			// 元画像y座標.
	const int& bw,			// 元画像幅.
	const int& bh,			// 元画像高さ.
	const float& angle )	// 角度.
{
	LONG	hx = ( bw / 2 );	// 矩形の横半分
	LONG	hy = ( bh / 2 );	// 矩形の縦半分
	LONG	radius = static_cast<LONG>(sqrtl( ( hx * hx ) + ( hy * hy ) ));	// 矩形の回転半径
	POINT	po[3];				// 矩形の回転頂点

	const float M_PI = 3.14f;
	const float M_PI_2 = M_PI/2.0f;
	const float M_PI_4 = M_PI/4.0f;

	// 左上隅
	float an = angle - ( M_PI_4 + M_PI_2 );
	po[0].x = ( cx + static_cast<LONG>(ceill( cosl(an) * radius )) );
	po[0].y = ( cy + static_cast<LONG>(ceill( sinl(an) * radius )) );
	// 右上隅
	an += M_PI_2;
	po[1].x = ( cx + static_cast<LONG>(ceill( cosl(an) * radius )) );
	po[1].y = ( cy + static_cast<LONG>(ceill( sinl(an) * radius )) );
	// 左下隅
	an += M_PI;
	po[2].x = ( cx + static_cast<LONG>(ceill( cosl(an) * radius )) );
	po[2].y = ( cy + static_cast<LONG>(ceill( sinl(an) * radius )) );

	GetInstance()->CreatMask(GetInstance()->m_hMemDC, bx, by, bw, bh );

	PlgBlt(
		GetInstance()->m_hScreenDC,
		po, 
		GetInstance()->m_hMemDC,
		bx, by, 
		bw, bh,
		GetInstance()->m_hmaskBMP,
		0, 0 );

	DeleteObject( GetInstance()->m_hmaskBMP );
	DeleteObject( GetInstance()->m_hmaskBitmapDC );
}

void CImage::bitBlt (
	const int& x, 		// 表示先x座標.
	const int& y,		// 表示先y座標.
	const int& w,		// 表示幅.
	const int& h,		// 表示高さ.
	const int& bx, 		// 元画像x座標.
	const int& by)		// 元画像y座標.
{
	BitBlt (
		GetInstance()->m_hScreenDC,
		x, y,	
		w, h,	
		GetInstance()->m_hMemDC,
		bx, by,		
		SRCCOPY );
}

void CImage::CreatMask( HDC hMemDC, int bx, int by, int sx, int sy )
{
	GetInstance()->oldBkColor = SetBkColor(
		hMemDC, RGB( 0x00, 0xFF, 0x00 ) );//背景色設定

	GetInstance()->m_hmaskBitmapDC = CreateCompatibleDC( nullptr );

	GetInstance()->m_hmaskBMP = CreateBitmap(
		sx, sy, 1, 1, nullptr);

	SelectObject( GetInstance()->m_hmaskBitmapDC, GetInstance()->m_hmaskBMP );

	//マスクビットマップを描画
	BitBlt(
		GetInstance()->m_hmaskBitmapDC,
		0, 0,
		sx, sy,
		hMemDC,
		bx, by,
		NOTSRCCOPY );

	//背景色を元に戻す
	SetBkColor( hMemDC, GetInstance()->oldBkColor );
}