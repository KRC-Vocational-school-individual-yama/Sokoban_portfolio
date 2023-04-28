#pragma once

#include"libs/object.h"

class MouseEdit :public Object {
public:
	MouseEdit(Scene* sc)					;
	~MouseEdit()			override		;
	void Init()				override		;
	void Update()			override		;
	void Draw()				override		;
private:
		//�`�b�v�ԍ��擾
	void MouseWhoweel()						;
		//�`�b�v�̓���ւ�
	void GameScene()						;
		//�}�E�X���W�̐��K��
	Vec2 MousePosEdit(const Vec2 mousePos)	;


	Vec2 mousePos							;//�}�E�X���W
	int nowNum								;//�`�b�v�ԍ�
};

