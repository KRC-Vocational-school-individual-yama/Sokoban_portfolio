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
	/// field�ւ�setter
	/// </summary>
	/// <param name="pos	">���W</param>
	/// <param name="chip	">�ԍ�</param>
	void SetFieldInside(Vec2 pos, int chip)											;
	
	/// <summary>
	/// �񎟌��@�v�f�ϊ��@�ꎟ��
	/// </summary>
	/// <param name="x			"			>i</param>
	/// <param name="y			"			>j</param>
	/// <param name="maxHorizontal=10	"	>�����̍ő��</param>
	/// <param name="max=99			"		>�v�f�̍ő吔</param>
	/// <returns></returns>
	static int IndexChange(int x, int y, int maxHorizontal = 10, int max = 99)		;
	/// <summary>
	/// �񎟌��@�v�f�ϊ��@�ꎟ�� verVec2
	/// </summary>
	/// <param name="pos			"		> i : j </param>
	/// <param name="maxHorizontal=10	"	>�����̍ő��</param>
	/// <param name="max=99			"		>�v�f�̍ő吔</param>
	/// <returns></returns>
	static int IndexChange(Vec2 pos, int maxHorizontal = 10, int max = 99)			;

	/// <summary>
	/// field�̒��g�����o��
	/// </summary>
	/// <param name="x	">i</param>
	/// <param name="y	">j</param>
	/// <returns></returns>
	int GetfieldInside(const int x, const int y)									;
	/// <summary>
	/// field�̒��g�����o��
	/// </summary>
	/// <param name="pos	"> i : j </param>
	/// <returns></returns>
	int GetfieldInside(const Vec2 pos)												;
	/// <summary>
	/// �S�[���F�̐��K���@getter
	/// </summary>
	/// <param name="pos	">���W</param>
	/// <returns></returns>
	int GetClearColor(const Vec2 pos)												;
		// ����Player�ʒu��Ⴄ getter
	Vec2 GetPlayerStart()															;
		//	����Box�ʒu��Ⴄ getter
	std::vector<Vec2> GetBoxStart()													;
		// �����N���A�ʒu��Ⴄ getter
	std::vector<Vec2> GetClearPos()													;
	
private:
		//field �̒��g��csv�ɕۑ�
	void Save()																		;
		//field ��csv����擾
	void Load()																		;
		//fieldChip �f�[�^�e�[�u��
	Vec2 ChipSelect(FieldInsideNumber fieldNum)										;
		//DrawBox�̈�����Vec2�ő�p
	void DrawBoxVec2(Vec2 upLeft, Vec2 downRight, unsigned int color, bool full) {
		DrawBox(upLeft.x, upLeft.y, downRight.x, downRight.y, color, full)			;
	}

	std::vector<int>field	;//inChips
	int hImage				;//�摜
	int xShaftMaxNum		;//��dfor�� j���[�v(y)��
	bool keystop			;
};