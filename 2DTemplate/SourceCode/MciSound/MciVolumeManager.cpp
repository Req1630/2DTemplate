#include "MciVolumeManager.h"

CMciVolumeManager::CMciVolumeManager()
	: m_fVolume		( 1.0f )
	, m_fBgmVolume	( VOLUME_MAX )
	, m_fSeVolume	( VOLUME_MAX )
{
}

CMciVolumeManager::~CMciVolumeManager()
{
}

void CMciVolumeManager::Increase( float& volume, const float& change, const float& max )
{
	volume += change;
	volume = volume >= max ? max : volume;
}

void CMciVolumeManager::VolumeIncrease()
{
	GetInstance()->Increase( 
		GetInstance()->m_fVolume,
		GetInstance()->MASTER_VALUE_TO_CHANGE,
		GetInstance()->MASTER_VOLUME_MAX );
	CMciSoundManager::SetVolume( GetInstance()->m_fVolume );
}

void CMciVolumeManager::BGMVolumeIncrease()
{
	GetInstance()->Increase(
		GetInstance()->m_fBgmVolume,
		GetInstance()->VALUE_TO_CHANGE,
		GetInstance()->VOLUME_MAX);
	CMciSoundManager::SetBGMVolume( GetInstance()->m_fBgmVolume );
}

void CMciVolumeManager::SEVolumeIncrease()
{
	GetInstance()->Increase(
		GetInstance()->m_fSeVolume,
		GetInstance()->VALUE_TO_CHANGE,
		GetInstance()->VOLUME_MAX);
	CMciSoundManager::SetSEVolume( GetInstance()->m_fSeVolume );
}

void CMciVolumeManager::Decrease( float& volume, const float& change, const float& min )
{
	volume -= change;
	volume = volume <= min ? min : volume;
}

void CMciVolumeManager::VolumeDecrease()
{
	GetInstance()->Decrease(
		GetInstance()->m_fVolume,
		GetInstance()->MASTER_VALUE_TO_CHANGE,
		GetInstance()->MASTER_VOLUME_MIN );
	CMciSoundManager::SetVolume( GetInstance()->m_fVolume );
}

void CMciVolumeManager::BGMVolumeDecrease()
{
	GetInstance()->Decrease(
		GetInstance()->m_fBgmVolume,
		GetInstance()->VALUE_TO_CHANGE,
		GetInstance()->VOLUME_MIN );
	CMciSoundManager::SetBGMVolume( GetInstance()->m_fBgmVolume );
}

void CMciVolumeManager::SEVolumeDecrease()
{
	GetInstance()->Decrease(
		GetInstance()->m_fSeVolume,
		GetInstance()->VALUE_TO_CHANGE,
		GetInstance()->VOLUME_MIN );
	CMciSoundManager::SetSEVolume( GetInstance()->m_fSeVolume );
}

void CMciVolumeManager::VolumeDraw( HDC hDC )
{
#ifdef _DEBUG
	std::string M_Volume = "master : " + std::to_string( GetInstance()->m_fVolume );
	std::string B_Volume = "bgm : " + std::to_string( GetInstance()->m_fBgmVolume );
	std::string S_Volume = "se : " + std::to_string( GetInstance()->m_fSeVolume );
	

	//FPS‚Ì•\Ž¦.
	TextOut( hDC, 10, 10, M_Volume.c_str(), M_Volume.length() );
	TextOut( hDC, 10, 40, B_Volume.c_str(), B_Volume.length() );
	TextOut( hDC, 10, 70, S_Volume.c_str(), S_Volume.length() );

#endif	// #ifdef _DEBUG.
}