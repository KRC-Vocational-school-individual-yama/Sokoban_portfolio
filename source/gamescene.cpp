#include "gamescene.h"

#include"gamescenechanger.h"
#include"player.h"
#include"field.h"
#include"movebox.h"
#include"backimage.h"
#include"mouseedit.h"
#include"clearpoint.h"
#include"backone.h"

GameScene::GameScene()
	:keystop(false)
{
	Create<BackImage>();
	Create<Field>();
	Create<ClearPoint>();
	Create<Player>();
	Create<MoveBox>();
	Create<GameSceneChanger>();
#ifdef _DEBUG
	Create<MouseEdit>();
#else
	Create<BackOne>();
#endif
}

GameScene::~GameScene(){
}

void GameScene::Update(){
	Scene::Update();


	//ƒŠƒZƒbƒg
	bool resetKey = CheckHitKey(KEY_INPUT_R);
	if (resetKey&&!keystop) {

		Player* player = Invoke<Player>();
		if(player!=nullptr)
			player->Reset();

		MoveBox* moveBox = Invoke<MoveBox>();
		if (moveBox != nullptr)
			moveBox->Reset();

		BackOne* backOne = Invoke<BackOne>();
		if (backOne != nullptr)
			backOne->Reset();
	}

	keystop = resetKey;
}
