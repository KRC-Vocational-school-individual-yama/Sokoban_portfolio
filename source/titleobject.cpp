#include "titleobject.h"

#include"libs/scenemanager.h"

TitleObject::TitleObject(Scene* sc)
	:Object				(sc)
	,keystop			(true)
	,endKeyStop			(true)
	,fontSizeChanger	(64.0f)
	,titleMoveSpeed		(0.05f)
{}
TitleObject::~TitleObject(){
}
void TitleObject::Init(){
}
void TitleObject::Update(){
	
	ChangeScene();

	TitleMoveAnim();

}
void TitleObject::Draw(){
	//�^�C�g������
	std::string titleName="";
#ifdef _DEBUG
	titleName = "TitleScene";
#else
	titleName = " �q �� �� ";
#endif

	int oldFontSize=GetFontSize();
	int setSize = static_cast<int>(fontSizeChanger);// 64;
	SetFontSize(setSize);

	int x = 400 - titleName.size() * setSize / 4;
	int y = 200 - setSize /2;
	DrawFormatString(x,y,0xeeeeee, titleName.c_str());

	SetFontSize(oldFontSize);


	//���V�[���փL�[�������Ă镶���̓_��
	bool alphaFlag = SceneManager::GetFrame() % 60 > GetRand(20);
	if (alphaFlag)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);

	DrawFormatString(300,400,0xffffff,"�X�y�[�X�L�[�������đq�ɔ�");

	if(alphaFlag)
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}



bool TitleObject::EndKeyInput(){

	bool endKey = CheckHitKey(KEY_INPUT_ESCAPE);
	if (endKey&&!endKeyStop) 
		return true;
	
	endKeyStop = endKey;
	return false;
}

void TitleObject::ChangeScene() {
	bool sceneKey = CheckHitKey(KEY_INPUT_SPACE)||CheckHitKey(KEY_INPUT_RETURN);
	if (sceneKey && !keystop) 
		SceneManager::SceneChange("Select");
	
#ifdef _DEBUG
	bool backKey = CheckHitKey(KEY_INPUT_TAB);
	if (backKey && !keystop) 
		SceneManager::SceneChange("boot");
	
	keystop = sceneKey || backKey;
#else
	keystop = sceneKey ;
#endif
}

void TitleObject::TitleMoveAnim(){
	const int fSize = static_cast<int>(fontSizeChanger);

	//�ő�ŏ� �� ���]
	if		(fSize == static_cast<int>(64*1.2f)	){
		titleMoveSpeed *= -1;
	}
	else if (fSize == static_cast<int>(64 * 0.9f)) {
		titleMoveSpeed *= -1;
	}

	fontSizeChanger+= titleMoveSpeed;
}
