#include "titlescene.h"

#include"libs/scenemanager.h"
#include"titleobject.h"
#include"selected.h"

TitleScene::TitleScene(){
	Create<TitleObject>();
#ifdef _DEBUG
#else
	SceneManager::GetCommonScene()->Create<SelectedField>();
#endif
}
TitleScene::~TitleScene(){
}
