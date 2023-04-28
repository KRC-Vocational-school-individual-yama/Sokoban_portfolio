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
		//チップ番号取得
	void MouseWhoweel()						;
		//チップの入れ替え
	void GameScene()						;
		//マウス座標の正規化
	Vec2 MousePosEdit(const Vec2 mousePos)	;


	Vec2 mousePos							;//マウス座標
	int nowNum								;//チップ番号
};

