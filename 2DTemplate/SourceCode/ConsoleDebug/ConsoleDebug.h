#ifndef CONSOlE_DEBUG_H
#define CONSOlE_DEBUG_H

#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>

#include "..\SingletonBase\SingletonBase.h"

class CConsoleDebug : public tpl::singleton<CConsoleDebug>
{
	const int MAX_THREAD_NUM = 3;
public:
	CConsoleDebug();
	~CConsoleDebug();

	static void ThreadInit()
	{
#ifdef _DEBUG
		GetInstance()->m_th_num = std::thread::hardware_concurrency();
		if( GetInstance()->m_th_num >= GetInstance()->MAX_THREAD_NUM ){
			GetInstance()->m_th = std::thread( GetInstance()->Main );
		}
#endif	// #ifdef _DEBUG.
	}

	static void ThreadRelease()
	{
#ifdef _DEBUG
		if( GetInstance()->m_th_num >= GetInstance()->MAX_THREAD_NUM ){
			GetInstance()->End();
			GetInstance()->m_th.join();
		}
#endif	// #ifdef _DEBUG.
	}

	//
	// �����̓ǂݍ���(�ψ���).
	//
	template<class... T1>
	static void print( const T1&... t1 )
	{
#ifdef _DEBUG
		if( GetInstance()->m_isDraw == true ) return;
		GetInstance()->m_sLog.emplace_back( GetInstance()->initstring(t1...) );
#endif	// #ifdef _DEBUG.
	}

	//
	//	���C�����[�v�̍Ō�ɋL�q.
	//
	static void SetDraw()
	{ 
#ifdef _DEBUG
		GetInstance()->m_isDraw = true; 
#endif	// #ifdef _DEBUG.
	}

private:
	//
	// �X���b�h�ɐݒ�.
	//
	static void Main()
	{
#ifdef _DEBUG
		GetInstance()->Init();
		while( GetInstance()->m_isEnd )
		{
			if( GetInstance()->m_isDraw ) GetInstance()->Draw();
		}
		GetInstance()->Release();
#endif	// #ifdef _DEBUG.
	}


	//
	//	�Q�[���̉���̍ۂɋL�q.
	//
	static void End()
	{
#ifdef _DEBUG
		GetInstance()->m_isEnd = false;
#endif	// #ifdef _DEBUG.
	}

	// ������.
	void Init();
	// ���.
	void Release();
	// �����o��(�ŏI�I�ɓǂݍ��񂾕������o��).
	void Draw();

	template <class T>
	std::string to_std_string(const T& x)
	{
		std::stringstream ss;
		ss << x;
		return ss.str();
	}
	template<class T1, class... T2>
	std::string initstring( const T1& t1, const T2&... t2 )
	{
		std::string s = to_std_string(t1);
		return s + initstring(t2...);
	}
	template<class T1>
	std::string initstring( const T1& t1 )
	{
		std::string s = to_std_string(t1);
		return s;
	}

private:
	FILE*		m_pf;
	HANDLE		m_pHandle;
	bool		m_isEnd;
	bool		m_isDraw;
	int			m_th_num;
	std::thread	m_th;
	std::vector<std::string> m_sLog;
};

#endif	// #ifndef CONSOlE_DEBUG_H.