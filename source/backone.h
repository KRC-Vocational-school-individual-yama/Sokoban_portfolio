#pragma once

#include"libs/object.h"

class BackOne :public Object {
public:
	BackOne(Scene* sc)						;
	~BackOne()		override				;
	void Init()		override				;
	void Update()	override				;
	void Draw()		override				;
	void Reset()							;//再初期化

	/// <summary>
	/// Playerの位置と向きを保存
	/// </summary>
	/// <param name="dir	">現在の向き</param>
	/// <param name="pos	">現在の座標</param>
	void PushToPlayer(int dir,Vec2 pos)		;
	/// <summary>
	/// 箱の位置を保存
	/// </summary>
	/// <param name="index	">箱の番号(要素数)</param>
	/// <param name="pos	">座標</param>
	void PushToBoxPos(int index,Vec2 pos)	;

		// Playerの位置を取得 getter
	Vec2 GetToPlayerPos()					;
		// 箱の向きを取得 getter
	int GetToPlayerDir()					;
		// 番号に合わせた箱の位置を取得
	Vec2 GetToBoxPos(int index)				;
	
private:
		// 各リストに初期位置を保存する　初めの一回のみ
	void FastPos()							;
		// 各リストの保存上限
	void Limit()							;

	std::list<Vec2>playerPosList			;//プレイヤーの座標
	std::list<int>playerDirList				;//プレイヤーの向き
	std::vector<std::list<Vec2>>boxPosList	;//各箱の座標
};