#pragma once

#include"libs/object.h"

class TitleObject :public Object {
public:
	TitleObject(Scene* sc)	;
	~TitleObject()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	/// <summary>
	/// 終了するキーを押したか
	/// </summary>
	/// <param name="true	">押した</param>
	/// <param name="false	">押してない</param>
	/// <returns></returns>
	bool EndKeyInput()		;

private:
		//シーン切り替えの入力受付
	void ChangeScene()		;
		//タイトルの拡縮
	void TitleMoveAnim()	;

	float fontSizeChanger	;//タイトル文字大きさ
	float titleMoveSpeed	;//動き量(vector)
	bool keystop			;
	bool endKeyStop			;//終了キー
};