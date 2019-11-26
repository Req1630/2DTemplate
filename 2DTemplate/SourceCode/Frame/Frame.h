#ifndef FRAME_H
#define FRAME_H

#include "..\Global.h"

class CFrame
{
public:
	CFrame();
	~CFrame();

	void Init();
	void Update( HWND hWnd );
	void Draw( HDC hDC );

	DWORD GetFrameNum(){ return s_dwFrames; };

private:
	static DWORD s_dwFrames;	// フレーム数.
	DWORD m_dwBeforeTime;		// 前の時間.
	char m_sFPS[32];

	DWORD m_dwNowTime;		// 現在の時間.
	DWORD m_dwProgress;		// 経過時間.
	DWORD m_dwIdealTime;	// 理想時間.
	
};

#endif	// #ifndef FRAME_H.