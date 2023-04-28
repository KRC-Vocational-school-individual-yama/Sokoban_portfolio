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
	printfDx("LCtrol+Skey  で保存\n"		);
	printfDx("左クリックで　入れ替え\n"		);
	printfDx("マウスホイールで　変更\n"		);
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
		case ffInside::empty					:printfDx("今のチップは　削除\n"				);		break;
		case ffInside::normal					:printfDx("今のチップは　床\n"					);		break;
		case ffInside::wall						:printfDx("今のチップは　壁\n"					);		break;
		case ffInside::playerStart				:printfDx("今のチップは　最初プレイヤー位置\n"	);		break;	
		case ffInside::boxStart					:printfDx("今のチップは　最初箱位置\n"			);		break;
		case ffInside::gool_Bule				:printfDx("今のチップは　青クリア位置\n"		);		break;
		case ffInside::boxStartAndGool_Bule		:printfDx("今のチップは　箱＆青クリア位置\n"	);		break;
		case ffInside::gool_Green				:printfDx("今のチップは　緑クリア位置\n"		);		break;
		case ffInside::boxStartAndGool_Green	:printfDx("今のチップは　箱＆緑クリア位置\n"	);		break;
		case ffInside::gool_Red					:printfDx("今のチップは　赤クリア位置\n"		);		break;
		case ffInside::boxStartAndGool_Red		:printfDx("今のチップは　箱＆赤クリア位置\n"	);		break;
		case ffInside::gool_Yellow				:printfDx("今のチップは　黄クリア位置\n"		);		break;
		case ffInside::boxStartAndGool_Yellow	:printfDx("今のチップは　箱＆黄クリア位置\n"	);		break;
		case ffInside::max						:printfDx("今のチップは　最大数\n"				);		break;
		default:								 printfDx("今のチップは　想定外\n"				);		break;
	}
}



void MouseEdit::MouseWhoweel() {

	nowNum -= GetMouseWheelRotVol();

	//下限上限
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

	//mousePos位置調整
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
	Vec2 pos			= _mousePos									;//変換前座標

	Vec2 startOffsets	= { START_OFFSET_POSX ,START_OFFSET_POSY }	;//オフセット
	Vec2 bodySize		= { BODY_SIZE ,BODY_SIZE }					;//大きさ
	Vec2 halfBodySize	= bodySize / Vec2{ 2,2 }					;//半分の大きさ

	pos -= startOffsets	;
	pos -= halfBodySize	;
	pos += bodySize		;
	pos /= bodySize		;

	return pos;
}
