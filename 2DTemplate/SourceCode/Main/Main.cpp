#include "main.h"
#include "..\Global.h"
#include "..\Frame\Frame.h"							// �t���[���N���X.
#include "..\XInput\XInput.h"						// XInput�N���X.
#include "..\MciSound\MciSoundManager.h"			// MciSound�N���X
#include "..\Image\Image.h"							// �摜�N���X.
#include "..\Image\ImageResource.h"					// �摜���\�[�X�N���X.
#include "..\Scene\SceneManager\SceneManager.h"		// �V�[���}�l�[�W���[�N���X.
#include "..\Scene\Scenes\GameScene\GameScene.h"
#include "..\ConsoleDebug\ConsoleDebug.h"			// �R���\�[���f�o�b�O.

#include <thread>

//�گ�ފ֐�.
DWORD WINAPI ThreadFunc( LPVOID vdParam )
{
	//�ϐ��錾.
	GameWindow *gameWnd;//�ްѳ���޳�\����.
	//�ްѳ���޳�\���̂��擾.
	gameWnd = (GameWindow*)vdParam;//�擪���ڽ�𷬽Ă��Ĉڂ�.

	//------------------------------------------------
	//	�N������[WM_CREATE].
	//------------------------------------------------
	//���DC�̍쐬.
	HDC hMemDC = CreateCompatibleDC( nullptr );
	CImage::Create( gameWnd->hScreenDC, hMemDC );

	CImageResource::Load( hMemDC );
	CMciSoundManager::Load( gameWnd->hWnd );

	std::unique_ptr<CFrame> pFrame = std::make_unique<CFrame>();	// �t���[���N���X.
	std::shared_ptr<clsSceneManager> pSceneManager = std::make_unique<clsSceneManager>();
	pSceneManager->Push( std::make_shared<clsGameScene>(pSceneManager) );	// �V�[���N���X.

	CConsoleDebug::ThreadInit();
	
	//����޳��������܂Ŗ���ٰ��.
	while( !gameWnd->isCloseWnd )
	{
		pFrame->Init();
		CXInput::StatsUpdate();
		CMciSoundManager::Update();
		//------------------------------------------------
		//	�ްя���[WM_TIMER].
		//------------------------------------------------
		pSceneManager->Update();

		//------------------------------------------------
		//	�`�揈��[WM_PAINT].
		//------------------------------------------------
		CImage::SetBitmap("backGround");
		CImage::bitBlt( 0, 0, 640, 480, 0, 0 );
		pSceneManager->Draw( gameWnd->hScreenDC, hMemDC );

		CConsoleDebug::SetDraw();

		pFrame->Draw( gameWnd->hScreenDC );
		pFrame->Update( gameWnd->hWnd );
	}

	//------------------------------------------------
	//	�������[WM_DESTROY].
	//------------------------------------------------
	CImageResource::Release();
	CMciSoundManager::Release();
	
	pSceneManager->Release();
	pSceneManager.~shared_ptr();
	pFrame.~unique_ptr();

	//���DC�̉��.
	DeleteDC( hMemDC );


	// �X���b�h�I���ʒm.
	ExitThread(0);

	return TRUE;
}

//����޳�֐�.
LRESULT CALLBACK WindowProc(
	HWND hWnd,		//����޳�����.
	UINT uMsg,		//ү����.
	WPARAM wParam,	//ү���ނɑ΂�����.
	LPARAM lParam )	//ү���ނɑ΂�����.
{
	HDC hdc;	//���޲���÷��.
	PAINTSTRUCT ps;//�`��\����.
	//-------------------------------------
	//	�گ�ފ֘A.
	//-------------------------------------
	static GameWindow gameWnd;//�ްѳ���޳�\����.
	static HANDLE th;
	DWORD dwID;		//�گ��ID.
	HBITMAP hBmp;	//�ޯ�ϯ�������.

	//ү���ޕʂ̏���.
	switch( uMsg ){
	case WM_DESTROY://����޳���j�����ꂽ��.
		//���ع���݂̏I����Windows�ɒʒm����.
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:	//����޳���������ꂽ��.
		
		//------------------------------------
		//	�گ�ނ̐ݒ�.
		//------------------------------------
		//�گ�ނɓn���l��ݒ�.
		gameWnd.hWnd = hWnd;	//����޳�����.
		gameWnd.size.cx = WND_W;//����޳��.
		gameWnd.size.cy = WND_H;//����޳����.
		gameWnd.dwFPS = FPS;	//FPS�l(�).

		//HDC�̍쐬.
		hdc = GetDC( hWnd );//DC(���޲���÷��)���擾.

		//�ޯ�ϯ������ق��쐬.
		hBmp = CreateCompatibleBitmap(
			hdc,
			gameWnd.size.cx,
			gameWnd.size.cy );

		//DC�ƌ݊����̂���DC���쐬.
		gameWnd.hScreenDC = CreateCompatibleDC(hdc);

		//hScreenDC���ޯ�ϯ�ߗp�Ƃ��Ē�`.
		SelectObject( gameWnd.hScreenDC, hBmp );

		//�s�v�ɂȂ���DC�����.
		ReleaseDC( hWnd, hdc );

		//�گ�ނ̍쐬�Ǝ��s.
		CreateThread(
			nullptr,//����ق𑼂���۾��Ƌ��L����ꍇ�͎w��.
			0,					//��������(��̫��:0).
			ThreadFunc,			//�گ�ފ֐���.
			(LPVOID)&gameWnd,	//�گ�ނɓn���\����.
			0,					//0:�쐬�Ɠ����Ɏ��s.
			&dwID);				//(out)�گ��ID.

		return 0;

	case WM_PAINT:	//����޳���X�V���ꂽ��.
		//�`��J�n.
		hdc = BeginPaint( hWnd, &ps );

		BitBlt(
			hdc,	//�\��DC.
			0, 0,	//�\����x,y���W.
			gameWnd.size.cx,//�\�����镝.
			gameWnd.size.cy,//�\�����鍂��.
			gameWnd.hScreenDC,//�ޯ��ޯ̧(�گ�ޓ��ō쐬).
			0, 0,	//���摜��x,y���W.
			SRCCOPY);//��߰����.

		 //�`��I��.
		EndPaint( hWnd, &ps );
		return 0;
	case WM_KEYDOWN://���������ꂽ.
		//���ʂ̏���.
		switch (wParam) {
		case VK_ESCAPE:	//Esc.
			if (MessageBox(nullptr,
				"�ްт��I�����܂����H", "�x��",
				MB_YESNO) == IDYES)
			{
				gameWnd.isCloseWnd = TRUE;
			}
			break;
		}
		if (!gameWnd.isCloseWnd) break;
	case WM_CLOSE:
		DWORD result;
		gameWnd.isCloseWnd = TRUE;
		while (1) {
			//�X���b�h���I��������`�F�b�N
			GetExitCodeThread(th, &result);
			//�I�������n���h�������B
			if (STILL_ACTIVE != result) {
				//closehandle�ŕ���B
				CloseHandle(th);
				//���[�v�𔲂���B
				break;
			}
		}

		CConsoleDebug::ThreadRelease();
		//����޳��j������.
		DestroyWindow(hWnd);
		return 0;
	}

	//Ҳ݂ɕԂ����.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//���C���֐�.
int WINAPI WinMain(
	HINSTANCE hInstance,	//�C���X�^���X�ԍ�(����޳�̔ԍ�).
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdshow )
{
	WNDCLASS wc;	//�E�B���h�E�N���X�\����.
	HWND hWnd;		//�E�B���h�E�n���h��.
	MSG msg;		//���b�Z�[�W.
	// �A�C�R���̍쐬
//	HICON res_icon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );

	//------------------------------------------------
	//	����CPU�ɑΉ������遥.
	//------------------------------------------------
	DWORD	ProcessAffinitMask;	//CPU���w��.
	HANDLE	hProcess;	//��۾������.
	DWORD	errnum;		//�װNo.
	BOOL	ret;		//�֐����A�l.



	//���g����۾�������ق��擾.
	hProcess = GetCurrentProcess();

	//���g�𓮍삳����CPU���w�肷��.
	ProcessAffinitMask = 1;	//CPU0���g��(2�i���Ŏw�肷��).
	ret = SetProcessAffinityMask(
		hProcess,
		ProcessAffinitMask );
	if( ret == FALSE ){
		errnum = GetLastError();	//�װ�����擾.
		return 0;
	}

	//------------------------------------------------
	//	����CPU�ɑΉ������遣.
	//------------------------------------------------

	//�E�B���h�E�N���X�̓o�^.
	wc.style = CS_HREDRAW | CS_VREDRAW;	//�X�^�C���̓o�^.
	wc.lpfnWndProc = WindowProc;		//�E�B���h�E�֐��̓o�^(DefWindowProc:��̫��).
	wc.hInstance = hInstance;			//�C���X�^���X�ԍ��̓o�^.
	wc.hIcon = nullptr;					//�A�C�R���̓o�^.
	wc.hCursor = nullptr;					//�J�[�\���̓o�^.
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;	//�w�i�F.
	wc.lpszMenuName = nullptr;				//���j���[�̓o�^.
	wc.cbClsExtra = 0;					//�g���p�����o(�g��Ȃ��̂łO�ŌŒ�).
	wc.cbWndExtra = 0;					//�g���p�����o(�g��Ȃ��̂łO�ŌŒ�).
	wc.lpszClassName = APP_NAME;		//�A�v���P�[�V������.

										//�E�B���h�E�N���X��Windows�ɓo�^.
	if ( !RegisterClass ( &wc ) ){
		MessageBox ( nullptr, "�E�B�h�E�N���X�̓o�^�Ɏ��s",
			"�װ", MB_OK );
		return 0;
	}

	//�E�B���h�E�̈�̒���.
	RECT rect;		//�Z�`�\����.
	RECT deskrect;

	rect.left	= 0;	//��.
	rect.top	= 0;	//��.
	rect.right	= WND_W;//�E.
	rect.bottom = WND_H;//��.

						// WS_OVERLAPPEDWINDOW, WS_POPUP.


	if ( !AdjustWindowRect (
		&rect,	//(in)��ʃT�C�Y���������Z�`�\���́A(out)�v�Z����.
		(WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME|WS_MAXIMIZEBOX)),//�E�B���h�E�X�^�C��.
		FALSE ))	//���j���[�������ǂ���.
	{
		MessageBox (nullptr,
			"�E�B���h�E�̈�̒����Ɏ��s",
			"�G���[", MB_OK );
		return 0;
	}
	SystemParametersInfo(SPI_GETWORKAREA, 0, &deskrect, 0);


	//����޳�̍쐬.
	hWnd = CreateWindow(
		APP_NAME,	//���ع���ݖ�(�\���̂Ɠ������O�ɂ���).
		WND_TITLE,	//����޳����.
		(WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME|WS_MAXIMIZEBOX)),	//����޳���.
		(((deskrect.right - deskrect.left) - (rect.right - rect.left)) / 2 + deskrect.left), 
		(((deskrect.bottom - deskrect.top) - (rect.bottom - rect.top)) / 2 + deskrect.top),		//�\���ʒux,y.
		rect.right - rect.left,	//�E�B���h�E�̕�.
		rect.bottom - rect.top,	//����޳�̍���.
		nullptr,		//�e����޳�������.
		nullptr,		//�ƭ��̐ݒ�.
		hInstance,	//�ݽ�ݽ�ԍ�.
		nullptr);//����޳�쐬���ɔ����������Ăɓn���ް�.

	if( hWnd == nullptr ){
		MessageBox( nullptr, "����޳�̍쐬�Ɏ��s",
			"�װ", MB_OK );
		return 0;
	}

	
	//�E�B���h�E�̕\��.
	ShowWindow ( hWnd, SW_SHOW ); 
	//SW_SHOW:�\���ASW_HIDE:��\��.
	//���b�Z�[�W���[�v.
	while ( GetMessage ( &msg, nullptr, 0, 0 ) > 0 ){
		//�E�B���h�E�֐��Ƀ��b�Z�[�W�𑗂�,
		DispatchMessage ( &msg );
	}
	
	return 0;
}
