#pragma once

#include"libs/object.h"

class ClearPoint :public Object {
public:
	ClearPoint(Scene* sc)			;
	~ClearPoint()			override;
	void Init()				override;
	void Update()			override;
	void Draw()				override;
		//再初期化
	void Reset()					;

	/// <summary>
	/// 箱が全てクリアに乗っているか
	/// </summary>
	/// <param name="true	">クリア</param>
	/// <param name="false	">クリアしてない</param>
	/// <returns></returns>
	bool GetClear()					;
private:
		// 箱がクリアにあるかを検知し onBox 配列に bool を入れる
	void CheckOnBox(int i)			;

	int hImage						;//画像
	std::vector<Vec2>pos			;//座標
	std::vector<Vec2>disp			;//表示位置
	std::vector<int>count			;//アニメーションカウンター
	std::vector<int>myColor			;//色情報
	std::vector<bool>onBox			;//箱が乗っているか
};