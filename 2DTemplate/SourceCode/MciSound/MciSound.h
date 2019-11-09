#ifndef MCI_SOUND_H
#define MCI_SOUND_H

#include <Windows.h>
#include <string>
#include <vector>

#include "..\SingletonBase\SingletonBase.h"

//ライブラリ読込.
#pragma comment ( lib, "winmm.lib" )

//文字列バッファ.
#define STR_BUFF_MAX 256

/***********************************************************
*	サウンドクラス.
*	midi, mp3 wav形式のファイルの再生・停止を行う.
**/
class CMciSound : tpl::singleton<CMciSound>
{
	
public:
	CMciSound();	// コンストラクタ.
	CMciSound(std::string sFName, std::string sAlias, HWND hWnd)
		: CMciSound()
	{
		Open( sFName, sAlias, hWnd );
	}

	~CMciSound();	// デストラクタ.

	// 音声ファイルを開く.
	static bool Open( std::string sFName, std::string sAlias, HWND hWnd );

	// 音声ファイルを閉じる.
	static bool Close ( std::string sAlias );

	// 再生.
	static bool Play ( std::string sAlias, bool bNotify = false );

	// 停止.
	static bool Stop ( std::string sAlias );

	// 曲の状態を取得する.
	bool GetStatus ( std::string sAlias, char* sStatus );

	// 音の停止を確認する.
	static bool IsStopped ( std::string sAlias );

	// 音の再生中を確認する.
	static bool IsPlaying ( std::string sAlias );

	// 再生位置を最初に戻す.
	static bool SeekToStart ( std::string sAlias );

	// 音量を設定する.
	static bool SetVolume( std::string sAlias, int value );

	int iBgmFlag;	// BGMフラグ.

private:
	

	HWND m_hWnd;		// ウィンドウハンドル.
	std::vector<std::string> m_Alias;// エイリアス.

	//初期設定.
	void SetInParam ( std::string sAlias, HWND hWnd );
};



#endif //#ifndef MCI_SOUND_H.