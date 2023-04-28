#pragma once

#include"libs/scene.h"

class GameScene :public Scene {
public:
	GameScene();
	~GameScene();
	void Update()override;
private:
	bool keystop;
};