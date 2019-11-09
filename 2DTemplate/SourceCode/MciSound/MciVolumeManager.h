#ifndef MCI_VOLUME_MANAGER_H
#define MCI_VOLUME_MANAGER_H

#include "MciSoundManager.h"
#include "..\SingletonBase\SingletonBase.h"

class CMciVolumeManager : tpl::singleton<CMciVolumeManager>
{
	const float MASTER_VOLUME_MAX		= 1.0f;
	const float MASTER_VOLUME_MIN		= 0.1f;
	const float MASTER_VALUE_TO_CHANGE	= 0.01f;

	const float VOLUME_MAX		= 1000.0f;
	const float VOLUME_MIN		= 100.0f;
	const float VALUE_TO_CHANGE = 5.0f;
public:
	CMciVolumeManager();
	virtual ~CMciVolumeManager();

	static void VolumeIncrease();
	static void BGMVolumeIncrease();
	static void SEVolumeIncrease();

	static void VolumeDecrease();
	static void BGMVolumeDecrease();
	static void SEVolumeDecrease();

	static void VolumeDraw( HDC hDC );

private:
	void Increase( float& volume, const float& change, const float& max );
	void Decrease( float& volume, const float& change, const float& min );

private:
	float m_fVolume;
	float m_fBgmVolume;
	float m_fSeVolume;
};

#endif	// #ifndef MCI_VOLUME_MANAGER_H.