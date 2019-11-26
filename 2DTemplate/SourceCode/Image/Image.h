#ifndef IMAGE_H
#define IMAGE_H

#include <Windows.h>
#include "..\SingletonBase\SingletonBase.h"
#include <string>

//�w��F�𓧉߂��ĕ`�悷�鏈���ŕK�v.
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

	// �摜�ǂݍ��݊֐�.
	static bool LoadBmp( HBITMAP *hBmp, const char* filename );
	static HBITMAP LoadBmp( const std::string& filename );

	static void SetBitmap( const std::string& filename, HBITMAP hBitmap = nullptr );

	//���ߕ\��.
	static void trnsBlt( 
		const int& x,	// �\����x���W.
		const int& y,	// �\����y���W.
		const int& w,	// �\����.
		const int& h,	// �\������.
		const int& bx,	// ���摜x���W.
		const int& by );// ���摜y���W.

						//�������\��.
	static void alphaBlt ( 
		const int& x,			// �\����x���W.
		const int& y,			// �\����y���W.
		const int& w,			// �\����.
		const int& h,			// �\������.
		const int& bx,			// ���摜x���W.
		const int& by,			// ���摜y���W.
		const int& alpha );		// ���ߒl(�A���t�@�l).

								// �g�k�\��.
	static void strchBlt(
		const int& x,	// �\����x���W.
		const int& y,	// �\����y���W.
		const int& w,	// �\����.
		const int& h,	// �\������.
		const int& bx,	// ���摜x���W.
		const int& by,	// ���摜y���W.
		const int& bw,	// ���摜��.
		const int& bh );// ���摜����.

						// ��]�\��.
	static void plgBlt(
		const int& cx,			// �\���� ���Sx���W.
		const int& cy,			// �\���� ���Sy���W.
		const int& bx,			// ���摜x���W.
		const int& by,			// ���摜y���W.
		const int& bw,			// ���摜��.
		const int& bh,			// ���摜����.
		const float& angle );	// �p�x.

								// �r�b�g�\��.
	static void bitBlt ( 
		const int& x, 		// �\����x���W.
		const int& y,		// �\����y���W.
		const int& w,		// �\����.
		const int& h,		// �\������.
		const int& bx, 		// ���摜x���W.
		const int& by );	// ���摜y���W.

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