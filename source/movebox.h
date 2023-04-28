#pragma once

#include"libs/object.h"

class MoveBox :public Object {
public :
	MoveBox(Scene* sc)							;
	~MoveBox()		override					;
	void Init()		override					;
	void Update()	override					;
	void Draw()		override					;
		//�S�Ă̈ʒu�����Z�b�g
	void Reset()								;

	
	/// <summary>
	/// �����x�N�g���ɂ��ړ�
	/// </summary>
	/// <param name="i	">���̗v�f��</param>
	/// <param name="vec	">�����x�N�g��</param>
	void MoveWhere(int i,Vec2 vec)				;
		//1�߂�̍��W�L�^
	void PushPoss()								;
		//1�߂�̍��W�K�p
	void MoveBack()								;
	/// <summary>
	/// ���Wgetter
	/// </summary>
	/// <param name="_i"> index</param>
	/// <returns></returns>
	Vec2 GetPos(int _i){ return pos[_i]; }		//�ȉ��Q�b�^�[
	/// <summary>
	/// ���W�ɂ��锠�̗v�f�����擾
	/// </summary>
	/// <param name="_pos">���W</param>
	/// <returns></returns>
	const int GetIndex(Vec2 _pos)				;
		//���@�v�f�̍ő吔���擾
	const int GetMaxIndex() { return maxIndex; }
private:
	std::vector<Vec2>pos						;//���W
	std::vector<Vec2>disp						;//�\���ʒu
	std::vector<Vec2>nowMove					;//�c��ړ���
	int hImage									;//�摜
	int maxIndex								;//�v�f�̍ő吔
};