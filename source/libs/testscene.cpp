#include "testscene.h"

#include"scenemanager.h"
#include"testplayer.h"
#include"../selected.h"

TestScene::TestScene() {
	Create<Test>();
	SceneManager::GetCommonScene()->Create<SelectedField>();
}
TestScene::~TestScene(){
}

