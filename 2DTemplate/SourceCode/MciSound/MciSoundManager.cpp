#include "MciSoundManager.h"
#include <crtdbg.h>

CMciSoundManager::CMciSoundManager()
	: m_fVolume			( MASTER_MAX_VOLUME )
	, m_fBgmVolume		( MAX_VOLUME )
	, m_fSeVolume		( MAX_VOLUME )
{
}

CMciSoundManager::~CMciSoundManager()
{
}

void CMciSoundManager::Update()
{
	GetInstance()->PlayBGM();
}

bool CMciSoundManager::PlayBGM( std::string playName )
{
	GetInstance()->m_nowBgmName = playName;
	GetInstance()->BGMStopCheck();
	GetInstance()->m_oldBgmName = playName;
	CMciSound::SeekToStart( playName );
	return CMciSound::Play( playName );
}

bool CMciSoundManager::PlaySE( std::string playName )
{
	GetInstance()->m_nowSeName = playName;
	if( CMciSound::IsPlaying( playName ) == true ) return true;
	CMciSound::SeekToStart( playName );
	return CMciSound::Play( playName );
}

void CMciSoundManager::PlayBGM()
{
	if( m_nowBgmName == "" ) return;
	if( CMciSound::IsPlaying( m_nowBgmName ) == true ) return;
	CMciSound::SeekToStart( m_nowBgmName );
	CMciSound::Play( m_nowBgmName );
}

void CMciSoundManager::Load( HWND hWnd )
{
	GetInstance()->CreateSound( hWnd );
}

void CMciSoundManager::BGMStopCheck()
{
	if( CMciSound::IsPlaying( m_oldBgmName ) == true ){
		CMciSound::Stop( m_oldBgmName );
	}
}

void CMciSoundManager::Release()
{
	for( auto& b : GetInstance()->m_BgmList ){
		CMciSound::Close( b );
	}
	for( auto& s : GetInstance()->m_SeList ){
		CMciSound::Close( s );
	}
}

void CMciSoundManager::CreateSound( HWND hWnd )
{
	Sound_kName_vPath bgmPath, sePath;

	FilePathSearch( bgmPath, sePath );

	auto create = [&]( const Sound_kName_vPath& path )
	{
		for( auto& p : path){
			CMciSound::Open( p.second, p.first, hWnd );
		}
	};
	auto setList = []( const Sound_kName_vPath& path, std::vector<std::string>& list )
	{
		for( auto& b : path ){
			list.emplace_back( b.first );
		}
	};

	create( bgmPath );
	create( sePath );
	setList( bgmPath, m_BgmList );
	setList( sePath, m_SeList );
}

void CMciSoundManager::SetVolume( const float& value )
{
	GetInstance()->m_fVolume = value;
	GetInstance()->SetBGMVolume();
	GetInstance()->SetSEVolume();
}

void CMciSoundManager::SetBGMVolume( const float& value )
{
	GetInstance()->m_fBgmVolume = value;
	GetInstance()->SetVolume( GetInstance()->m_fBgmVolume, GetInstance()->m_BgmList );
}

void CMciSoundManager::SetSEVolume( const float& value )
{ 
	GetInstance()->m_fSeVolume = value;
	GetInstance()->SetVolume( GetInstance()->m_fSeVolume, GetInstance()->m_SeList );
}

void CMciSoundManager::SetVolume( const float& volume, std::vector<std::string>& List )
{
	int Volume = static_cast<int>(m_fVolume*volume);
	for (auto& l : List) {
		CMciSound::SetVolume(l, Volume);
	}
}

void CMciSoundManager::FilePathSearch( Sound_kName_vPath& bgmPath, Sound_kName_vPath& sePath )
{
	auto Se_Bgm_Search = [&]( const fs::directory_entry& entry )
	{
		std::string extension = entry.path().extension().string();
		std::string filename = entry.path().string();

		if( extension != ".mp3" &&
			extension != ".wav" &&
			extension != ".midi" ) return;

		if( filename.find("BGM") != std::string::npos ){
			bgmPath[entry.path().stem().string()] = entry.path().string();
		} else if( filename.find("SE") != std::string::npos ){
			sePath[entry.path().stem().string()] = entry.path().string();
		}
	};

	try {
		fs::recursive_directory_iterator dir_it(SOUND_FILE_PATH), end_it;
		std::for_each( dir_it, end_it, Se_Bgm_Search );

	} catch ( fs::filesystem_error e ) {
		std::string Message = e.what();
		_ASSERT_EXPR( false, L"ディレクトリ取得失敗" );
	}
}