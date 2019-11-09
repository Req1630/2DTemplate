#include "XInput.h"

CXInput::CXInput()
	: m_State			( FOUR_LIMITED_CONTROLLER )
	, m_ConnectedCount	( 0 )
{
}

CXInput::~CXInput()
{}

void CXInput::StatsUpdate()
{
	GetInstance()->m_ConnectedCount = 0;
	DWORD dwResult;
	for( size_t i = 0; i < GetInstance()->m_State.size(); i++ ){
		dwResult = XInputGetState( i, &GetInstance()->m_State[i] );
		if( dwResult == ERROR_SUCCESS ){
			GetInstance()->m_ConnectedCount++;
		}
	}
}

//--------------------------------.
// ボタン.
//--------------------------------.
bool CXInput::A_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_A );
}
bool CXInput::B_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_B );
}
bool CXInput::X_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_X );
}
bool CXInput::Y_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_Y );
}

//--------------------------------.
// 方向キー.
//--------------------------------.
bool CXInput::DPadUp( const int& connectNum, const bool& isKeyinput )
{
	GetInstance()->ConnectCheck( connectNum );
	if( isKeyinput == true ){
		return ( GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_UP ) ) ||
			( GetAsyncKeyState(VK_UP) & 0x8000 );
	} else {
		return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_UP );
	}
}
bool CXInput::DPadDown( const int& connectNum, const bool& isKeyinput )
{
	GetInstance()->ConnectCheck( connectNum );
	if( isKeyinput == true ){
		return ( GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_DOWN ) ) ||
			( GetAsyncKeyState(VK_DOWN) & 0x8000 );
	} else {
		return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_DOWN );
	}
}
bool CXInput::DPadLEFT( const int& connectNum, const bool& isKeyinput )
{
	GetInstance()->ConnectCheck( connectNum );
	if( isKeyinput == true ){
		return ( GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_LEFT ) ) ||
			( GetAsyncKeyState(VK_LEFT) & 0x8000 );
	} else {
		return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_LEFT );
	}
}
bool CXInput::DPadRIGHT( const int& connectNum, const bool& isKeyinput )
{
	GetInstance()->ConnectCheck( connectNum );
	if( isKeyinput == true ){
		return ( GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_RIGHT ) ) ||
			( GetAsyncKeyState(VK_RIGHT) & 0x8000 );
	} else {
		return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_DPAD_RIGHT );
	}
}

//--------------------------------.
// Lスティック.
//--------------------------------.
SHORT CXInput::LThumbX_Axis( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->m_State[connectNum].Gamepad.sThumbLX;
}
SHORT CXInput::LThumbY_Axis( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->m_State[connectNum].Gamepad.sThumbLY;
}
//--------------------------------.
// Rスティック.
//--------------------------------.
SHORT CXInput::RThumbX_Axis( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->m_State[connectNum].Gamepad.sThumbRX;
}
SHORT CXInput::RThumbY_Axis( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->m_State[connectNum].Gamepad.sThumbRY;
}

//--------------------------------.
// スティックボタン.
//--------------------------------.
bool CXInput::LThumb_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_LEFT_THUMB );
}
bool CXInput::RThumb_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_RIGHT_THUMB );
}

//--------------------------------.
// トリガー.
//--------------------------------.
INT CXInput::LTrigger( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->m_State[connectNum].Gamepad.bLeftTrigger;
}
INT CXInput::RTrigger( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->m_State[connectNum].Gamepad.bRightTrigger;
}

//--------------------------------.
// ショルダー.
//--------------------------------.
bool CXInput::L_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_LEFT_SHOULDER );
}
bool CXInput::R_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_RIGHT_SHOULDER );
}

//--------------------------------.
// スタート ボタン.
//--------------------------------.
bool CXInput::Start_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_START );
}
//--------------------------------.
// バック ボタン.
//--------------------------------.
bool CXInput::Back_Button( const int& connectNum )
{
	GetInstance()->ConnectCheck( connectNum );
	return GetInstance()->IsButtonInput( connectNum, XINPUT_GAMEPAD_BACK );
}


void CXInput::ConnectCheck( const int& connectNum )
{
	if( connectNum >= m_ConnectedCount ){
//		MessageBox( nullptr,
//			"コントローラーの数が足りません", "", MB_OK );
	}
}
bool CXInput::IsButtonInput( const int& connectNum, const DWORD& button_mask )
{
	return ( GetInstance()->m_State[connectNum].Gamepad.wButtons & button_mask );
}