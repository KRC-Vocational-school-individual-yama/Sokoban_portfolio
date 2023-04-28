#include "movebox.h"

#include"libs/scene.h"
#include"player.h"
#include"field.h"
#include"backone.h"

MoveBox::MoveBox(Scene* sc)
	:Object		(sc)
	,pos		()
	,disp		()
	,nowMove	()
	,hImage		(-1)
	,maxIndex	(0)
{
	pos.clear();
	disp.clear();
	nowMove.clear();
}
MoveBox::~MoveBox(){
	if(hImage>0)
		DeleteGraph(hImage);
}
void MoveBox::Init(){
	Field* field = GetScene()->Invoke<Field>()			;
	assert(CheckClass<Field>())							;

	pos			= field->GetBoxStart()					;

	maxIndex	= pos.size()							;
	disp.resize(maxIndex)								;
	nowMove.resize(maxIndex)							;

	hImage		= LoadGraph("data/texture/mapchip.png")	;
	assert(hImage > 0)									;
}
void MoveBox::Update() {
	using namespace PlayerConfig;
	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {

		//見える座標を移動
		disp[i].x		= pos[i].x * BODY_SIZE + START_OFFSET_POSX	;
		disp[i].y		= pos[i].y * BODY_SIZE + START_OFFSET_POSY	;

		//箱のアニメーション
		nowMove[i].x	= Player::DownDistance(nowMove[i].x)		;
		nowMove[i].y	= Player::DownDistance(nowMove[i].y)		;
	}
}
void MoveBox::Draw(){
	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {

		int radius	= PlayerConfig::BODY_SIZE / 2 - 1;
		Vec2 square = disp[i] + nowMove[i];

#ifdef _DEBUG
		//本体　
		DrawBox( square.x - radius, square.y - radius
				,square.x + radius,square.y + radius
				,0xdddd22, true);

		//装飾用（文字
		int fontS	= GetFontSize();
		SetFontSize(48);

		DrawFormatString(square.x - 10, square.y - 24, 0xffffff, "B");

		SetFontSize(fontS);
#else
		int widthSize = 256 / 8;
		int heightSize = 160 / 5;

		DrawRectExtendGraph(square.x - radius, square.y - radius, square.x + radius, square.y + radius
			, widthSize * 7, heightSize * 1, widthSize, heightSize, hImage, true);
#endif
	}
}

void MoveBox::Reset(){
	pos.clear()		;
	disp.clear()	;
	nowMove.clear()	;

	Field* field = GetScene()->Invoke<Field>();
	assert(CheckClass<Field>());

	pos = field->GetBoxStart();
	const int maxIndex = pos.size();

	disp.resize(maxIndex)	;
	nowMove.resize(maxIndex);

	using namespace PlayerConfig;
	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {
		disp[i].x = pos[i].x * BODY_SIZE + START_OFFSET_POSX;
		disp[i].y = pos[i].y * BODY_SIZE + START_OFFSET_POSY;
	}
}



void MoveBox::MoveWhere(int _i, Vec2 _vec){
	using namespace PlayerConfig				;
	Vec2 minnus		 = {-1,-1}					;
	Vec2 bodySize	 = { BODY_SIZE ,BODY_SIZE }	;

	pos[_i]			+= _vec						;
	nowMove[_i]		 = minnus * bodySize*_vec	;
}

void MoveBox::PushPoss(){
	BackOne* bo= GetScene()->Invoke<BackOne>();
	if (!CheckClass<BackOne>())
		return;

	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++)
		bo->PushToBoxPos(i,pos[i]);
}

void MoveBox::MoveBack(){
	BackOne* bo = GetScene()->Invoke<BackOne>();
	if (bo==nullptr)
		return;

	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++)
		pos[i]= bo->GetToBoxPos(i);
}

const int MoveBox::GetIndex(Vec2 _pos){
	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {
		if (pos[i]==_pos) 
			return i;
	}
	return -1;
}
