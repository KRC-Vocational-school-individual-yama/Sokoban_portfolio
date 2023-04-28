#pragma once

#include"libs/object.h"

class MoveBox :public Object {
public :
	MoveBox(Scene* sc)							;
	~MoveBox()		override					;
	void Init()		override					;
	void Update()	override					;
	void Draw()		override					;
		//全ての位置をリセット
	void Reset()								;

	
	/// <summary>
	/// 方向ベクトルによる移動
	/// </summary>
	/// <param name="i	">箱の要素数</param>
	/// <param name="vec	">方向ベクトル</param>
	void MoveWhere(int i,Vec2 vec)				;
		//1つ戻るの座標記録
	void PushPoss()								;
		//1つ戻るの座標適用
	void MoveBack()								;
	/// <summary>
	/// 座標getter
	/// </summary>
	/// <param name="_i"> index</param>
	/// <returns></returns>
	Vec2 GetPos(int _i){ return pos[_i]; }		//以下ゲッター
	/// <summary>
	/// 座標にある箱の要素数を取得
	/// </summary>
	/// <param name="_pos">座標</param>
	/// <returns></returns>
	const int GetIndex(Vec2 _pos)				;
		//箱　要素の最大数を取得
	const int GetMaxIndex() { return maxIndex; }
private:
	std::vector<Vec2>pos						;//座標
	std::vector<Vec2>disp						;//表示位置
	std::vector<Vec2>nowMove					;//残り移動量
	int hImage									;//画像
	int maxIndex								;//要素の最大数
};