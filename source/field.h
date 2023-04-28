#pragma once

#include"libs/object.h"

class Field :public Object {
public:
	enum class FieldInsideNumber {
		  empty = -1
		, normal
		, wall
		, playerStart
		, boxStart
		, gool_Bule
		, boxStartAndGool_Bule
		, gool_Green
		, boxStartAndGool_Green
		, gool_Red
		, boxStartAndGool_Red
		, gool_Yellow
		, boxStartAndGool_Yellow
		, max
	};

	Field(Scene* sc)																;
	~Field()		override														;
	void Init()		override														;
	void Update()	override														;
	void Draw()		override														;


	/// <summary>
	/// fieldへのsetter
	/// </summary>
	/// <param name="pos	">座標</param>
	/// <param name="chip	">番号</param>
	void SetFieldInside(Vec2 pos, int chip)											;
	
	/// <summary>
	/// 二次元　要素変換　一次元
	/// </summary>
	/// <param name="x			"			>i</param>
	/// <param name="y			"			>j</param>
	/// <param name="maxHorizontal=10	"	>横幅の最大回数</param>
	/// <param name="max=99			"		>要素の最大数</param>
	/// <returns></returns>
	static int IndexChange(int x, int y, int maxHorizontal = 10, int max = 99)		;
	/// <summary>
	/// 二次元　要素変換　一次元 verVec2
	/// </summary>
	/// <param name="pos			"		> i : j </param>
	/// <param name="maxHorizontal=10	"	>横幅の最大回数</param>
	/// <param name="max=99			"		>要素の最大数</param>
	/// <returns></returns>
	static int IndexChange(Vec2 pos, int maxHorizontal = 10, int max = 99)			;

	/// <summary>
	/// fieldの中身を取り出す
	/// </summary>
	/// <param name="x	">i</param>
	/// <param name="y	">j</param>
	/// <returns></returns>
	int GetfieldInside(const int x, const int y)									;
	/// <summary>
	/// fieldの中身を取り出す
	/// </summary>
	/// <param name="pos	"> i : j </param>
	/// <returns></returns>
	int GetfieldInside(const Vec2 pos)												;
	/// <summary>
	/// ゴール色の正規化　getter
	/// </summary>
	/// <param name="pos	">座標</param>
	/// <returns></returns>
	int GetClearColor(const Vec2 pos)												;
		// 初期Player位置を貰う getter
	Vec2 GetPlayerStart()															;
		//	初期Box位置を貰う getter
	std::vector<Vec2> GetBoxStart()													;
		// 初期クリア位置を貰う getter
	std::vector<Vec2> GetClearPos()													;
	
private:
		//field の中身をcsvに保存
	void Save()																		;
		//field をcsvから取得
	void Load()																		;
		//fieldChip データテーブル
	Vec2 ChipSelect(FieldInsideNumber fieldNum)										;
		//DrawBoxの引数をVec2で代用
	void DrawBoxVec2(Vec2 upLeft, Vec2 downRight, unsigned int color, bool full) {
		DrawBox(upLeft.x, upLeft.y, downRight.x, downRight.y, color, full)			;
	}

	std::vector<int>field	;//inChips
	int hImage				;//画像
	int xShaftMaxNum		;//二重forの jループ(y)回数
	bool keystop			;
};