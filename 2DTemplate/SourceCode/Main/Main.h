#ifndef MAIN_H
#define MAIN_H
#include <Windows.h>

//音声再生,およびｽﾚｯﾄﾞで使用する.
#pragma comment( lib, "winmm.lib" )

//構造体宣言.
typedef struct _GameWindow {
	HWND	hWnd;		//ｳｨﾝﾄﾞｳﾊﾝﾄﾞﾙ.
	HDC		hScreenDC;	//ﾊﾞｯｸﾊﾞｯﾌｧ.
	SIZE	size;		//ｻｲｽﾞ.
	DWORD	dwFPS;//FPS(Frame Per Second:ﾌﾚｰﾑ/秒).
	BOOL	isCloseWnd;
} GameWindow;

#endif	// #ifndef MAIN_H.