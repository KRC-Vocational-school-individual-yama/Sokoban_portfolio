#pragma once

#include"libs/object.h"

class SelectMode :public Object {
public:
	SelectMode(Scene* sc)										;
	~SelectMode()	override									;
	void Init()		override									;
	void Update()	override									;
	void Draw()		override									;

private:
		//ステージの数を保存
	void SaveStageNum()											;
		//上下左右の入力受付
	void Update_UpDownLeftRight(const std::vector<bool>& key)	;
		//ステージの増減
	void Update_InCreateDestroy(const std::vector<bool>& key)	;

	bool keystop												;
	int stage													;//選んだステージ
	int maxStage												;//ステージの最大数
	std::vector<std::string>dispStr								;//ステージの数だけ表示する

};