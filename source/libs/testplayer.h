#pragma once

#include"object.h"

class Test :public Object {
public:
	Test(Scene* sc);
	~Test()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	void Move()				;//���͎�t
	void Dash()				;//���肩������
	void SceneChangeKey()	;//�V�[���̐؂�ւ���t

	std::string freeStr		;//�Z���t
	Vec2 player				;//���W
	int radius				;
	int speed				;
};