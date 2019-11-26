#include "Image.h"
#include "ImageResource.h"
#include "..\Global.h"

void CImage::Create( HDC hScreenDC, HDC hMemDC )
{
	GetInstance()->m_hScreenDC = hScreenDC;
	GetInstance()->m_hMemDC = hMemDC;
	GetInstance()->m_hWorkDC = CreateCompatibleDC ( hScreenDC );//��ƗpDC�쐬.
	GetInstance()->m_hWorkBMP = CreateCompatibleBitmap (hScreenDC, WND_W*2, WND_H*2 );//��Ɨp�r�b�g�}�b�v�쐬.
	SelectObject ( GetInstance()->m_hWorkDC, GetInstance()->m_hWorkBMP );	//DC�ƃr�b�g�}�b�v�̊֘A�t��.
}

bool CImage::LoadBmp( HBITMAP *hBmp, const char* filename )
{
	//�w�i�̓ǂݍ���.
	*hBmp = ( HBITMAP ) LoadImage (
		NULL,				//�C���X�^���X�ԍ�(�ȗ�).
		filename,			//�t�@�C����.
		IMAGE_BITMAP,		//�r�b�g�}�b�v�`��.
		0, 0,				//�ǂݍ��މ摜��x, y���W.
		LR_LOADFROMFILE );	//�t�@�C������ǂݍ���.
	if ( *hBmp == NULL ) {
		MessageBox ( NULL,
			"�摜�t�@�C���̓ǂݍ��ݎ��s",
			filename, MB_OK );
		return false;
	}
	return true;
}

HBITMAP CImage::LoadBmp( const std::string& filename )
{
	try {
		return (HBITMAP)LoadImage(
			NULL,				//�C���X�^���X�ԍ�(�ȗ�).
			filename.c_str(),			//�t�@�C����.
			IMAGE_BITMAP,		//�r�b�g�}�b�v�`��.
			0, 0,				//�ǂݍ��މ摜��x, y���W.
			LR_LOADFROMFILE);	//�t�@�C������ǂݍ���.
	} catch ( const std::exception& ) {
		MessageBox(NULL,
			"�摜�t�@�C���̓ǂݍ��ݎ��s",
			filename.c_str(), MB_OK);
	}

}

void CImage::SetBitmap( const std::string& filename, HBITMAP hBitmap )
{
	const HBITMAP bmp = hBitmap == nullptr 
		? CImageResource::GetBitmap(filename) : hBitmap;
	SelectObject( GetInstance()->m_hMemDC, bmp );
}

//���ߕ\��.
void CImage::trnsBlt(
	const int& x,	// �\����x���W.
	const int& y,	// �\����y���W.
	const int& w,	// �\����.
	const int& h,	// �\������.
	const int& bx,	// ���摜x���W.
	const int& by)	// ���摜y���W.
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

//�������\��.
void CImage::alphaBlt(
	const int& x,			// �\����x���W.
	const int& y,			// �\����y���W.
	const int& w,			// �\����.
	const int& h,			// �\������.
	const int& bx,			// ���摜x���W.
	const int& by,			// ���摜y���W.
	const int& alpha )		// ���ߒl(�A���t�@�l).
{
	//���ߍ\����.
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
	const int& x,	// �\����x���W.
	const int& y,	// �\����y���W.
	const int& w,	// �\����.
	const int& h,	// �\������.
	const int& bx,	// ���摜x���W.
	const int& by,	// ���摜y���W.
	const int& bw,	// ���摜��.
	const int& bh )	// ���摜����.
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
	const int& cx,			// �\���� ���Sx���W.
	const int& cy,			// �\���� ���Sy���W.
	const int& bx,			// ���摜x���W.
	const int& by,			// ���摜y���W.
	const int& bw,			// ���摜��.
	const int& bh,			// ���摜����.
	const float& angle )	// �p�x.
{
	LONG	hx = ( bw / 2 );	// ��`�̉�����
	LONG	hy = ( bh / 2 );	// ��`�̏c����
	LONG	radius = static_cast<LONG>(sqrtl( ( hx * hx ) + ( hy * hy ) ));	// ��`�̉�]���a
	POINT	po[3];				// ��`�̉�]���_

	const float M_PI = 3.14f;
	const float M_PI_2 = M_PI/2.0f;
	const float M_PI_4 = M_PI/4.0f;

	// �����
	float an = angle - ( M_PI_4 + M_PI_2 );
	po[0].x = ( cx + static_cast<LONG>(ceill( cosl(an) * radius )) );
	po[0].y = ( cy + static_cast<LONG>(ceill( sinl(an) * radius )) );
	// �E���
	an += M_PI_2;
	po[1].x = ( cx + static_cast<LONG>(ceill( cosl(an) * radius )) );
	po[1].y = ( cy + static_cast<LONG>(ceill( sinl(an) * radius )) );
	// ������
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
	const int& x, 		// �\����x���W.
	const int& y,		// �\����y���W.
	const int& w,		// �\����.
	const int& h,		// �\������.
	const int& bx, 		// ���摜x���W.
	const int& by)		// ���摜y���W.
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
		hMemDC, RGB( 0x00, 0xFF, 0x00 ) );//�w�i�F�ݒ�

	GetInstance()->m_hmaskBitmapDC = CreateCompatibleDC( nullptr );

	GetInstance()->m_hmaskBMP = CreateBitmap(
		sx, sy, 1, 1, nullptr);

	SelectObject( GetInstance()->m_hmaskBitmapDC, GetInstance()->m_hmaskBMP );

	//�}�X�N�r�b�g�}�b�v��`��
	BitBlt(
		GetInstance()->m_hmaskBitmapDC,
		0, 0,
		sx, sy,
		hMemDC,
		bx, by,
		NOTSRCCOPY );

	//�w�i�F�����ɖ߂�
	SetBkColor( hMemDC, GetInstance()->oldBkColor );
}