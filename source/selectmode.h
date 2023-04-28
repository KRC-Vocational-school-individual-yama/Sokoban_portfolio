#pragma once

#include"libs/object.h"

class SelectMode :public Object {
public:
	SelectMode(Scene* sc)										;
	~SelectMode()	override									;
	void Init()		override									;
	void Update()	override									;
	void Draw()		override									;

private:
		//�X�e�[�W�̐���ۑ�
	void SaveStageNum()											;
		//�㉺���E�̓��͎�t
	void Update_UpDownLeftRight(const std::vector<bool>& key)	;
		//�X�e�[�W�̑���
	void Update_InCreateDestroy(const std::vector<bool>& key)	;

	bool keystop												;
	int stage													;//�I�񂾃X�e�[�W
	int maxStage												;//�X�e�[�W�̍ő吔
	std::vector<std::string>dispStr								;//�X�e�[�W�̐������\������

};