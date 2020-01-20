#include "XinputConfig.h"

CXInputConfig::CXInputConfig()
{
	m_Button["A"] = XINPUT_GAMEPAD_A;
	m_Button["B"] = XINPUT_GAMEPAD_B;
	m_Button["X"] = XINPUT_GAMEPAD_X;
	m_Button["Y"] = XINPUT_GAMEPAD_Y;
	m_Button["Left"] = XINPUT_GAMEPAD_LEFT_SHOULDER;
	m_Button["Right"] = XINPUT_GAMEPAD_RIGHT_SHOULDER;
}

CXInputConfig::~CXInputConfig()
{
	m_Button.clear();
}