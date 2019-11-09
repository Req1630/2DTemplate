#include "MciSound.h"

#include <crtdbg.h>

//コンストラクタ.
CMciSound::CMciSound()
	: m_hWnd	( nullptr )
	, iBgmFlag	( 0 )
{}

//デストラクタ.
CMciSound::~CMciSound()
{
	m_hWnd = nullptr;
}

//初期設定.
void CMciSound::SetInParam ( std::string sAlias, HWND hWnd )
{
	//ウィンドウハンドルを設定.
	m_hWnd = hWnd;

	//エイリアスを設定.
	m_Alias.emplace_back( sAlias );
}

//音声ファイルを開く.
bool CMciSound::Open ( std::string sFName, std::string sAlias, HWND hWnd )
{
	//初期設定.
	GetInstance()->SetInParam ( sAlias, hWnd );
	MCIERROR mciError;

	//コマンド.
	std::string cmd = "open " + sFName + " alias " + sAlias;

	mciError = mciSendString( cmd.c_str(), nullptr, 0, hWnd );
	
	if( mciError != 0 ){
		_ASSERT_EXPR( false, L"音声ファイルが見つかりません" );
		return false;
	}
	return true;
}

//音声ファイルを閉じる.
bool CMciSound::Close( std::string sAlias )
{
	//コマンド.
	std::string cmd = "close " + sAlias;

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//再生.
bool CMciSound::Play ( std::string sAlias, bool bNotify )
{
	//コマンド.
	std::string cmd = "play " + sAlias;

	if ( bNotify == true ){
		cmd += " notify";
		//notify 処理が終了した時にMM_MCINOTIFY	メッセージをポストする.
	}

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//停止.
bool CMciSound::Stop( std::string sAlias )
{
	//コマンド.
	std::string cmd = "stop " + sAlias;

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//曲の状態を取得する.
//　※状態を取得する場合は、再生時に｢notfy｣を設定し,
//		ウィンドウハンドルにメッセージを送っておく必要がある.
bool CMciSound::GetStatus ( std::string sAlias, char* sStatus )
{
	std::string cmd = "status " + sAlias + " mode";

	if ( mciSendString ( cmd.c_str(), sStatus, STR_BUFF_MAX, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//音の停止を確認する.
bool CMciSound::IsStopped ( std::string sAlias )
{
	char sStatus[STR_BUFF_MAX] = "";

	//状態を取得.
	if ( GetInstance()->GetStatus ( sAlias, sStatus )){
		//文字列比較.
		if ( strcmp ( sStatus, "stopped" ) == 0 ){
			return true;
		}
	}
	return false;
}

//音の再生中を確認する.
bool CMciSound::IsPlaying ( std::string sAlias )
{
	char sStatus[STR_BUFF_MAX] = "";

	//状態を取得.
	if ( GetInstance()->GetStatus ( sAlias, sStatus )){
		//文字列比較.
		if ( strcmp ( sStatus, "playing" ) == 0 ){
			return true;
		}
	}
	return false;
}

//再生位置を最初に戻す.
bool CMciSound::SeekToStart ( std::string sAlias )
{
	//コマンド.
	std::string cmd = "seek " + sAlias + " to start";

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

bool CMciSound::SetVolume( std::string sAlias, int value )
{
	std::string s_value = std::to_string(value);
	std::string cmd = "setaudio " + sAlias + " volume to " + s_value;
	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}