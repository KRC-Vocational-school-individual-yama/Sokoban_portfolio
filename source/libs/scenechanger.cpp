#include "scenechanger.h"

#include<Windows.h>
#include<assert.h>

#include"testscene.h"
#include"scene.h"
#include"../titlescene.h"
#include"../gamescene.h"
#include"../stageselect.h"


Scene* SceneChanger::Changer(std::string scene) {
#ifdef _DEBUG
	if		(scene == "boot")		return new TestScene()		;
	else
#endif 
	if		(scene == "Title")		return new TitleScene()		;
	else if (scene == "Select")		return new StageSelect()	;
	else if (scene == "Game")		return new GameScene()		;
	else {
		MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + scene).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
		assert(false);
		return nullptr;
	}

}
