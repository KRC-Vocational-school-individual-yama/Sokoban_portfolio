#pragma once

#include"libs/object.h"

namespace PlayerConfig {
	static const int BODY_SIZE = 58			;//�v���C���[�̑傫��
	static const int START_OFFSET_POSX = 240;//�����ʒu�̒���X
	static const int START_OFFSET_POSY = 40	;//�����ʒu�̒���Y

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
	/// ��ΐ���0�Ɍ��炵�Ă����@*=0.�`�@�Ǝ��Ă���
	/// </summary>
	/// <param name="_obj">���炷��ΐ�</param>
	/// <returns></returns>
	static int DownDistance(int _obj )	;
		//geter
	Vec2 GetPos() { return pos; }
private:
		//�ړ��x�N�g���ɉ������\���ړ�
	void MoveWhere(Vec2 _vec)			;
		//���͎�t
	void Move()							;
		//Plyaer�@���̕���
	void StrDraw(Vec2 square)			;

	Vec2 pos							;//���W
	Vec2 disp							;//�\�����W
	Vec2 nowMove						;//�ړ��A�j���[�V��������
	bool fillFlag						;//�h��Ԃ�
	bool isStop							;//�~�܂��Ă��邩
	bool keystop						;
	int size							;//Player�̑傫��
	int hImage							;//�摜
	int direction						;//PlyaerDirection
	int moveAnim						;//charaChip�̐���

	enum class PlayerDirection {
		front
		,left
		,right
		,back
		,max
	};

};