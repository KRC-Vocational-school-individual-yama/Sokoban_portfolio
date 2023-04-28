#pragma once

#include"libs/object.h"

class GameSceneChanger :public Object {
public:
	GameSceneChanger(Scene* sc)	;
	~GameSceneChanger()	override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

private:
		//それぞれの入力受付とシーン変更を司る
	void Change()				;

	bool keystop				;
};