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
		//���ꂼ��̓��͎�t�ƃV�[���ύX���i��
	void Change()				;

	bool keystop				;
};