#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "..\..\SceneBase\SceneBase.h"

class clsGameScene : public clsSceneBase
{
public:
	clsGameScene( std::shared_ptr<clsSceneManager> &sceneManager );
	~clsGameScene();

	void Updata() override;
	void Draw( HDC hScreenDC, HDC hMemDC ) override;
};

#endif // #ifndef GAME_SCENE_H.