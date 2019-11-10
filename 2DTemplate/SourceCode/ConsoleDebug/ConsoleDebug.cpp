#include "ConsoleDebug.h"

CConsoleDebug::CConsoleDebug()
	: m_pf		( nullptr )
	, m_pHandle	( nullptr )
	, m_isEnd	( true )
	, m_isDraw	( false )
{
}

CConsoleDebug::~CConsoleDebug()
{
}

void CConsoleDebug::Init()
{
#ifdef _DEBUG
	AllocConsole();
	
	freopen_s( &GetInstance()->m_pf, "CONOUT$", "w", stdout );
	freopen_s( &GetInstance()->m_pf, "CONIN$", "r", stdin );

	GetInstance()->m_pHandle = GetStdHandle( STD_OUTPUT_HANDLE );

	SMALL_RECT rect = { 0, 0, 50, 30 };
	SetConsoleWindowInfo( GetInstance()->m_pHandle, TRUE, &rect );

	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo( GetInstance()->m_pHandle, &cci );
	cci.bVisible = FALSE;
	SetConsoleCursorInfo( GetInstance()->m_pHandle, &cci );

#endif	// #ifdef _DEBUG.
}

void CConsoleDebug::Release()
{
#ifdef _DEBUG
	CloseHandle( GetInstance()->m_pHandle );
//	FreeConsole();
#endif	// #ifdef _DEBUG.
}

void CConsoleDebug::Draw()
{
#ifdef _DEBUG
	int y = 0;
	COORD coord;
	coord.X = 0; coord.Y = 0;
	SetConsoleCursorPosition( GetInstance()->m_pHandle, coord );
	size_t count = GetInstance()->m_sLog.size();
	for( size_t i = 0; i < count; i++ ){
		std::cout << GetInstance()->m_sLog[i] << "                               " << std::endl;
		coord.Y++;
		SetConsoleCursorPosition( GetInstance()->m_pHandle, coord );
	}
	GetInstance()->m_sLog.clear();
	GetInstance()->m_isDraw = false;
#endif	// #ifdef _DEBUG.
}
