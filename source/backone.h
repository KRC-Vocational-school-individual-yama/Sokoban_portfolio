#pragma once

#include"libs/object.h"

class BackOne :public Object {
public:
	BackOne(Scene* sc)						;
	~BackOne()		override				;
	void Init()		override				;
	void Update()	override				;
	void Draw()		override				;
	void Reset()							;//�ď�����

	/// <summary>
	/// Player�̈ʒu�ƌ�����ۑ�
	/// </summary>
	/// <param name="dir	">���݂̌���</param>
	/// <param name="pos	">���݂̍��W</param>
	void PushToPlayer(int dir,Vec2 pos)		;
	/// <summary>
	/// ���̈ʒu��ۑ�
	/// </summary>
	/// <param name="index	">���̔ԍ�(�v�f��)</param>
	/// <param name="pos	">���W</param>
	void PushToBoxPos(int index,Vec2 pos)	;

		// Player�̈ʒu���擾 getter
	Vec2 GetToPlayerPos()					;
		// ���̌������擾 getter
	int GetToPlayerDir()					;
		// �ԍ��ɍ��킹�����̈ʒu���擾
	Vec2 GetToBoxPos(int index)				;
	
private:
		// �e���X�g�ɏ����ʒu��ۑ�����@���߂̈��̂�
	void FastPos()							;
		// �e���X�g�̕ۑ����
	void Limit()							;

	std::list<Vec2>playerPosList			;//�v���C���[�̍��W
	std::list<int>playerDirList				;//�v���C���[�̌���
	std::vector<std::list<Vec2>>boxPosList	;//�e���̍��W
};