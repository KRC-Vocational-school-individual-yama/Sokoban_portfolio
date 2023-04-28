#pragma once

#include"libs/object.h"

namespace PlayerConfig {
	static const int BODY_SIZE = 58			;//プレイヤーの大きさ
	static const int START_OFFSET_POSX = 240;//初期位置の調整X
	static const int START_OFFSET_POSY = 40	;//初期位置の調整Y

};

class Player :public Object {
public:
	Player(Scene* sc)					;
	~Player()		override			;
	void Init()		override			;
	void Update()	override			;
	void Draw()		override			;
	void Reset()						;

	/// <summary>
	/// 絶対数を0に減らしていく　*=0.～　と似ている
	/// </summary>
	/// <param name="_obj">減らす絶対数</param>
	/// <returns></returns>
	static int DownDistance(int _obj )	;
		//geter
	Vec2 GetPos() { return pos; }
private:
		//移動ベクトルに応じた十字移動
	void MoveWhere(Vec2 _vec)			;
		//入力受付
	void Move()							;
		//Plyaer　ｐの文字
	void StrDraw(Vec2 square)			;

	Vec2 pos							;//座標
	Vec2 disp							;//表示座標
	Vec2 nowMove						;//移動アニメーション推移
	bool fillFlag						;//塗りつぶし
	bool isStop							;//止まっているか
	bool keystop						;
	int size							;//Playerの大きさ
	int hImage							;//画像
	int direction						;//PlyaerDirection
	int moveAnim						;//charaChipの推移

	enum class PlayerDirection {
		front
		,left
		,right
		,back
		,max
	};

};