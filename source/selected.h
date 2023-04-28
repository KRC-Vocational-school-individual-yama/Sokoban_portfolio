#pragma once
#include"libs/object.h"

class SelectedField :public Object {
public:
	SelectedField(Scene* sc) 
		:Object		(sc)
		,selected	(0)	
	{}
	~SelectedField()	override{}
	void Init()			override{}
	void Update()		override{}
	void Draw()			override{}

	/// <summary>
	/// �I�񂾃X�e�[�W��ݒ�
	/// </summary>
	/// <param name="_num	">�X�e�[�W�i���o�[</param>
	void SetSelected(int _num) { selected = _num; }
	/// <summary>
	/// �I�񂾃X�e�[�W���擾
	/// </summary>
	/// <returns></returns>
	int GetSelected() { return selected; }
private:
	int selected;//�I�񂾃X�e�[�W
};