#ifndef MCI_SOUND_MANAGER_H
#define MCI_SOUND_MANAGER_H

#include <unordered_map>
#include <string>
#include <filesystem>
#include <functional>

#include "MciSound.h"
#include "..\SingletonBase\SingletonBase.h"

namespace fs = std::filesystem;

class CMciSoundManager : tpl::singleton<CMciSoundManager>
{
	typedef std::unordered_map<std::string, std::string> Sound_kName_vPath;

	const char* SOUND_FILE_PATH = "Data\\Sound";

	const float MASTER_MAX_VOLUME	= 1.0f;
	const float MAX_VOLUME	= 1000.0f;

public:
	CMciSoundManager();
	virtual ~CMciSoundManager();

	static void Update();
	static void Load( HWND hWnd );
	static void AllClose();

	static bool PlayBGM( std::string playName );
	static bool PlaySE( std::string playName );

	static void SetVolume( const float& value );
	static void SetBGMVolume( const float& value = GetInstance()->m_fBgmVolume );
	static void SetSEVolume( const float& value = GetInstance()->m_fSeVolume );

private:
	void PlayBGM();

	void BGMStopCheck();

	void CreateSound( HWND hWnd );
	void FilePathSearch( Sound_kName_vPath& bgmPath, Sound_kName_vPath& sePath );

	void SetVolume( const float& volume, std::vector<std::string>& List );

private:
	std::vector<std::string> m_BgmList;
	std::vector<std::string> m_SeList;
	std::string m_nowBgmName;
	std::string m_oldBgmName;
	std::string m_nowSeName;

	float m_fVolume;
	float m_fBgmVolume;
	float m_fSeVolume;
};

#endif	// #ifndef MCI_SOUND_MANAGER_H.