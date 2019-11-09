#ifndef MCI_SOUND_H
#define MCI_SOUND_H

#include <Windows.h>
#include <string>
#include <vector>

#include "..\SingletonBase\SingletonBase.h"

//���C�u�����Ǎ�.
#pragma comment ( lib, "winmm.lib" )

//������o�b�t�@.
#define STR_BUFF_MAX 256

/***********************************************************
*	�T�E���h�N���X.
*	midi, mp3 wav�`���̃t�@�C���̍Đ��E��~���s��.
**/
class CMciSound : tpl::singleton<CMciSound>
{
	
public:
	CMciSound();	// �R���X�g���N�^.
	CMciSound(std::string sFName, std::string sAlias, HWND hWnd)
		: CMciSound()
	{
		Open( sFName, sAlias, hWnd );
	}

	~CMciSound();	// �f�X�g���N�^.

	// �����t�@�C�����J��.
	static bool Open( std::string sFName, std::string sAlias, HWND hWnd );

	// �����t�@�C�������.
	static bool Close ( std::string sAlias );

	// �Đ�.
	static bool Play ( std::string sAlias, bool bNotify = false );

	// ��~.
	static bool Stop ( std::string sAlias );

	// �Ȃ̏�Ԃ��擾����.
	bool GetStatus ( std::string sAlias, char* sStatus );

	// ���̒�~���m�F����.
	static bool IsStopped ( std::string sAlias );

	// ���̍Đ������m�F����.
	static bool IsPlaying ( std::string sAlias );

	// �Đ��ʒu���ŏ��ɖ߂�.
	static bool SeekToStart ( std::string sAlias );

	// ���ʂ�ݒ肷��.
	static bool SetVolume( std::string sAlias, int value );

	int iBgmFlag;	// BGM�t���O.

private:
	

	HWND m_hWnd;		// �E�B���h�E�n���h��.
	std::vector<std::string> m_Alias;// �G�C���A�X.

	//�����ݒ�.
	void SetInParam ( std::string sAlias, HWND hWnd );
};



#endif //#ifndef MCI_SOUND_H.