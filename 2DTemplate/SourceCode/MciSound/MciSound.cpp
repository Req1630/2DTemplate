#include "MciSound.h"

#include <crtdbg.h>

//�R���X�g���N�^.
CMciSound::CMciSound()
	: m_hWnd	( nullptr )
	, iBgmFlag	( 0 )
{}

//�f�X�g���N�^.
CMciSound::~CMciSound()
{
	m_hWnd = nullptr;
}

//�����ݒ�.
void CMciSound::SetInParam ( std::string sAlias, HWND hWnd )
{
	//�E�B���h�E�n���h����ݒ�.
	m_hWnd = hWnd;

	//�G�C���A�X��ݒ�.
	m_Alias.emplace_back( sAlias );
}

//�����t�@�C�����J��.
bool CMciSound::Open ( std::string sFName, std::string sAlias, HWND hWnd )
{
	//�����ݒ�.
	GetInstance()->SetInParam ( sAlias, hWnd );
	MCIERROR mciError;

	//�R�}���h.
	std::string cmd = "open " + sFName + " alias " + sAlias;

	mciError = mciSendString( cmd.c_str(), nullptr, 0, hWnd );
	
	if( mciError != 0 ){
		_ASSERT_EXPR( false, L"�����t�@�C����������܂���" );
		return false;
	}
	return true;
}

//�����t�@�C�������.
bool CMciSound::Close( std::string sAlias )
{
	//�R�}���h.
	std::string cmd = "close " + sAlias;

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//�Đ�.
bool CMciSound::Play ( std::string sAlias, bool bNotify )
{
	//�R�}���h.
	std::string cmd = "play " + sAlias;

	if ( bNotify == true ){
		cmd += " notify";
		//notify �������I����������MM_MCINOTIFY	���b�Z�[�W���|�X�g����.
	}

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//��~.
bool CMciSound::Stop( std::string sAlias )
{
	//�R�}���h.
	std::string cmd = "stop " + sAlias;

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//�Ȃ̏�Ԃ��擾����.
//�@����Ԃ��擾����ꍇ�́A�Đ����ɢnotfy���ݒ肵,
//		�E�B���h�E�n���h���Ƀ��b�Z�[�W�𑗂��Ă����K�v������.
bool CMciSound::GetStatus ( std::string sAlias, char* sStatus )
{
	std::string cmd = "status " + sAlias + " mode";

	if ( mciSendString ( cmd.c_str(), sStatus, STR_BUFF_MAX, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//���̒�~���m�F����.
bool CMciSound::IsStopped ( std::string sAlias )
{
	char sStatus[STR_BUFF_MAX] = "";

	//��Ԃ��擾.
	if ( GetInstance()->GetStatus ( sAlias, sStatus )){
		//�������r.
		if ( strcmp ( sStatus, "stopped" ) == 0 ){
			return true;
		}
	}
	return false;
}

//���̍Đ������m�F����.
bool CMciSound::IsPlaying ( std::string sAlias )
{
	char sStatus[STR_BUFF_MAX] = "";

	//��Ԃ��擾.
	if ( GetInstance()->GetStatus ( sAlias, sStatus )){
		//�������r.
		if ( strcmp ( sStatus, "playing" ) == 0 ){
			return true;
		}
	}
	return false;
}

//�Đ��ʒu���ŏ��ɖ߂�.
bool CMciSound::SeekToStart ( std::string sAlias )
{
	//�R�}���h.
	std::string cmd = "seek " + sAlias + " to start";

	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

bool CMciSound::SetVolume( std::string sAlias, int value )
{
	std::string s_value = std::to_string(value);
	std::string cmd = "setaudio " + sAlias + " volume to " + s_value;
	if ( mciSendString ( cmd.c_str(), nullptr, 0, GetInstance()->m_hWnd ) == 0 ){
		return true;
	}
	return false;
}