#include "gamescenechanger.h"

#include"libs/scenemanager.h"
#include"clearpoint.h"

GameSceneChanger::GameSceneChanger(Scene* sc)
	:Object		(sc)
	,keystop	(false)
{}
GameSceneChanger::~GameSceneChanger(){
}
void GameSceneChanger::Init(){
}
void GameSceneChanger::Update(){

	//�펞�V�[���ύX�ҋ@
	Change();

	//�N���A�����Ƃ�
	ClearPoint* clearPoint = GetScene()->Invoke<ClearPoint>();
	assert(clearPoint != nullptr);

	if (clearPoint->GetClear()) 
		SceneManager::SceneChange("Select");
	
}
void GameSceneChanger::Draw(){
	//�V�[���ύX�̈ē�
	printfDx("Esc�L�[�@�Ń^�C�g���֖߂�\n"	);
	printfDx("R�L�[�@  �Ń��Z�b�g\n"		);
	printfDx("\n"							);
}
void GameSceneChanger::Change(){
	bool backKey	= CheckHitKey(KEY_INPUT_ESCAPE);

	if (backKey && !keystop) 
		SceneManager::SceneChange("Select");

#ifdef _DEBUG
	bool changeKey	= CheckHitKey(KEY_INPUT_TAB);
	if (changeKey && !keystop) 
		SceneManager::SceneChange("Select");
	
	keystop			= changeKey||backKey;
#else
	keystop = backKey;
#endif // _DEBUG
}
