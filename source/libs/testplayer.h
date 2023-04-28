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
	void Move()				;//入力受付
	void Dash()				;//走りか歩きか
	void SceneChangeKey()	;//シーンの切り替え受付

	std::string freeStr		;//セリフ
	Vec2 player				;//座標
	int radius				;
	int speed				;
};