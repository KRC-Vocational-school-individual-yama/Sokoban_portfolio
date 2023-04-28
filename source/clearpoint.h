#pragma once

#include"libs/object.h"

class ClearPoint :public Object {
public:
	ClearPoint(Scene* sc)			;
	~ClearPoint()			override;
	void Init()				override;
	void Update()			override;
	void Draw()				override;
		//�ď�����
	void Reset()					;

	/// <summary>
	/// �����S�ăN���A�ɏ���Ă��邩
	/// </summary>
	/// <param name="true	">�N���A</param>
	/// <param name="false	">�N���A���ĂȂ�</param>
	/// <returns></returns>
	bool GetClear()					;
private:
		// �����N���A�ɂ��邩�����m�� onBox �z��� bool ������
	void CheckOnBox(int i)			;

	int hImage						;//�摜
	std::vector<Vec2>pos			;//���W
	std::vector<Vec2>disp			;//�\���ʒu
	std::vector<int>count			;//�A�j���[�V�����J�E���^�[
	std::vector<int>myColor			;//�F���
	std::vector<bool>onBox			;//��������Ă��邩
};