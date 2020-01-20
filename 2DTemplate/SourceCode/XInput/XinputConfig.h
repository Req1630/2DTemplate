#ifndef XINPUT_CONFIG_H
#define XINPUT_CONFIG_H

#include <Windows.h>
#include <Xinput.h>
#include <memory>
#include <unordered_map>
#include <string>

#pragma comment( lib, "xinput.lib" )

class CXInputConfig
{
public:
	CXInputConfig();
	virtual ~CXInputConfig();

protected:
	std::unordered_map<std::string, DWORD> m_Button;
};

#endif	// #ifndef XINPUT_CONFIG_H.