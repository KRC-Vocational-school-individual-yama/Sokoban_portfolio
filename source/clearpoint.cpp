#include "clearpoint.h"

#include"libs/scene.h"
#include"field.h"
#include"player.h"
#include"movebox.h"

ClearPoint::ClearPoint(Scene* sc)
	:Object		(sc)
	,pos		()
	,disp		()
	,myColor	()
	,count		()
	,onBox		()
	,hImage		(-1)
{
	pos.clear()		;
	disp.clear()	;
	count.clear()	;
	onBox.clear()	;
	myColor.clear()	;
}
ClearPoint::~ClearPoint(){
	if(hImage>0)
		DeleteGraph(hImage);
}
void ClearPoint::Init(){
	Field* fClass		= GetScene()->Invoke<Field>()				;
	pos					= fClass->GetClearPos()						;
	const int maxIndex	= pos.size()								;
	
	disp.resize(maxIndex)											;
	count.resize(maxIndex)											;
	onBox.resize(maxIndex)											;
	myColor.resize(maxIndex)										;

	for (int i = 0; static_cast<unsigned int>(i) < pos.size();i++) {
		myColor[i]		= fClass->GetClearColor(pos[i])				;
	}

	hImage = LoadGraph("data/texture/goal.png")						;
	assert(hImage > 0)												;
}
void ClearPoint::Update(){
	using namespace PlayerConfig									;
	Vec2 bodySize	= { BODY_SIZE			, BODY_SIZE }			;
	Vec2 offsets	= { START_OFFSET_POSX	, START_OFFSET_POSY }	;

	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {

		//移動の動き
		disp[i]  = pos[i] * bodySize;
		disp[i] += offsets			;

		//アニメーション
		count[i]++					;

		//箱が乗っているか
		CheckOnBox(i)				;
	}
}
void ClearPoint::Draw(){
	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {

		const int radius = PlayerConfig::BODY_SIZE / 2 - 1;
		const Vec2 square = disp[i];
#ifdef _DEBUG

		const int colors[] = {
			0x2222dd,
			0x22dd22,
			0xdd2222,
			0xdddd22
		};

		//本体　
		DxLib::DrawBox(   square.x - radius, square.y - radius
						, square.x + radius, square.y + radius
						, colors[myColor[i]], true);

		//装飾用（文字
		int fontS = GetFontSize();
		DxLib::SetFontSize(48);

		DxLib::DrawFormatString(square.x - 10, square.y - 24, 0xffffff, "C");

		DxLib::SetFontSize(fontS);

		if (!onBox[i])
			continue;

		DxLib::printfDx("clear %d\n",i);
#else
		const int widthSize		= 192 / 3;
		const int heightSize	= 448 / 4;
		DrawRectExtendGraph(square.x - radius, square.y - radius-( radius*2), square.x + radius, square.y + radius
			, widthSize * (count[i]/7%3), heightSize * myColor[i], widthSize, heightSize, hImage, true);
#endif
	}
}

bool ClearPoint::GetClear(){
	int count=0;

	for (int i = 0; static_cast<unsigned int>(i) < onBox.size(); i++) {
		if (onBox[i])
			count++;
	}
	
	if (count == 0)
		return false;

	if (count == onBox.size())
		return true;
	
	return false;
}


void ClearPoint::Reset(){
	pos.clear()		;
	disp.clear()	;
	count.clear()	;
	onBox.clear()	;
	myColor.clear()	;

	Field* fClass = GetScene()->Invoke<Field>()	;
	assert(CheckClass<Field>())					;
	
	pos = fClass->GetClearPos()					;
	const int maxIndex = pos.size()				;
	
	disp.	resize(maxIndex)					;
	count.	resize(maxIndex)					;
	onBox.	resize(maxIndex)					;
	myColor.resize(maxIndex)					;

	using namespace PlayerConfig				;
	Vec2 bodySize	 = { BODY_SIZE			, BODY_SIZE}			;
	Vec2 offsets	 = { START_OFFSET_POSX	, START_OFFSET_POSY }	;

	for (int i = 0; static_cast<unsigned int>(i) < pos.size(); i++) {
		
		count[i]	 = 0							;
		onBox[i]	 = false						;
		myColor[i]	 = fClass->GetClearColor(pos[i]);

		disp[i]		 = pos[i] * bodySize			;
		disp[i]		+= offsets						;
	}
}

void ClearPoint::CheckOnBox(int i){
	onBox[i] = false;
	MoveBox* aBox	= GetScene()->Invoke<MoveBox>();
	if (!CheckClass<MoveBox>())
		return;

	const int index = aBox->GetIndex(pos[i]);
	if (index == -1)
		return;
	
	Vec2 aBoxPos	= aBox->GetPos(index);
	
	if (pos[i] == aBoxPos) 
		onBox[i]	= true;
}
