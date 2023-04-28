#include "mouseedit.h"

#include"libs/scene.h"
#include"field.h"
#include"player.h"
#include"movebox.h"
#include"clearpoint.h"

MouseEdit::MouseEdit(Scene* sc)
	:Object		(sc)
	,nowNum		(0)
	,mousePos	(Vec2{ 100,100 })
{}
MouseEdit::~MouseEdit(){
}
void MouseEdit::Init(){

}
void MouseEdit::Update() {
	
	MouseWhoweel();

	GetMousePoint(&mousePos.x, &mousePos.y);
	
	GameScene();
}
void MouseEdit::Draw(){
	printfDx("\n"							);
	printfDx("LCtrol+Skey  �ŕۑ�\n"		);
	printfDx("���N���b�N�Ł@����ւ�\n"		);
	printfDx("�}�E�X�z�C�[���Ł@�ύX\n"		);
	printfDx("\n"							);
	printfDx("mousePos .x= %d\n",mousePos.x	);
	printfDx("mousePos .y= %d\n",mousePos.y	);

	Vec2 mpos = MousePosEdit(mousePos)		 ;

	printfDx("posNums .x= %d\n", mpos.x		);
	printfDx("posNums .y= %d\n", mpos.y		);
	printfDx("\n"							);
	
	
	using ffInside= Field::FieldInsideNumber;
	ffInside nowChip = static_cast<ffInside>(nowNum);

	switch (nowChip){
		case ffInside::empty					:printfDx("���̃`�b�v�́@�폜\n"				);		break;
		case ffInside::normal					:printfDx("���̃`�b�v�́@��\n"					);		break;
		case ffInside::wall						:printfDx("���̃`�b�v�́@��\n"					);		break;
		case ffInside::playerStart				:printfDx("���̃`�b�v�́@�ŏ��v���C���[�ʒu\n"	);		break;	
		case ffInside::boxStart					:printfDx("���̃`�b�v�́@�ŏ����ʒu\n"			);		break;
		case ffInside::gool_Bule				:printfDx("���̃`�b�v�́@�N���A�ʒu\n"		);		break;
		case ffInside::boxStartAndGool_Bule		:printfDx("���̃`�b�v�́@�����N���A�ʒu\n"	);		break;
		case ffInside::gool_Green				:printfDx("���̃`�b�v�́@�΃N���A�ʒu\n"		);		break;
		case ffInside::boxStartAndGool_Green	:printfDx("���̃`�b�v�́@�����΃N���A�ʒu\n"	);		break;
		case ffInside::gool_Red					:printfDx("���̃`�b�v�́@�ԃN���A�ʒu\n"		);		break;
		case ffInside::boxStartAndGool_Red		:printfDx("���̃`�b�v�́@�����ԃN���A�ʒu\n"	);		break;
		case ffInside::gool_Yellow				:printfDx("���̃`�b�v�́@���N���A�ʒu\n"		);		break;
		case ffInside::boxStartAndGool_Yellow	:printfDx("���̃`�b�v�́@�������N���A�ʒu\n"	);		break;
		case ffInside::max						:printfDx("���̃`�b�v�́@�ő吔\n"				);		break;
		default:								 printfDx("���̃`�b�v�́@�z��O\n"				);		break;
	}
}



void MouseEdit::MouseWhoweel() {

	nowNum -= GetMouseWheelRotVol();

	//�������
	if (nowNum < -1)
		nowNum = -1;

	const int ffInsideMax = static_cast<int>(Field::FieldInsideNumber::max);
	if (nowNum > ffInsideMax - 1)
		nowNum = ffInsideMax - 1;

}

void MouseEdit::GameScene() {

	if (!CheckClass<Field>())
		return;

	bool change = (GetMouseInput() & MOUSE_INPUT_LEFT);
	if (!change)
		return;

	//mousePos�ʒu����
	Vec2 pos = MousePosEdit(mousePos);

	if (CheckClass<Field>())
		GetScene()->Invoke<Field>()->SetFieldInside(pos, nowNum);

	if (CheckClass<Player>())
		GetScene()->Invoke<Player>()->Reset();

	if (CheckClass<MoveBox>())
		GetScene()->Invoke<MoveBox>()->Reset();

	if (CheckClass<ClearPoint>())
		GetScene()->Invoke<ClearPoint>()->Reset();
}

Vec2 MouseEdit::MousePosEdit(const Vec2 _mousePos)
{
	using namespace PlayerConfig									;
	Vec2 pos			= _mousePos									;//�ϊ��O���W

	Vec2 startOffsets	= { START_OFFSET_POSX ,START_OFFSET_POSY }	;//�I�t�Z�b�g
	Vec2 bodySize		= { BODY_SIZE ,BODY_SIZE }					;//�傫��
	Vec2 halfBodySize	= bodySize / Vec2{ 2,2 }					;//�����̑傫��

	pos -= startOffsets	;
	pos -= halfBodySize	;
	pos += bodySize		;
	pos /= bodySize		;

	return pos;
}
