#include "player.h"

#include"libs/scene.h"
#include"field.h"
#include"movebox.h"
#include"backone.h"

namespace {
#ifdef _DEBUG
	static const int MOVE_SPEED = 8;//１フレームの移動量
#else
	static const int MOVE_SPEED	= 5;//１フレームの移動量
#endif
	static const int BODY_COLOR_KEY_INPUT = 0xd6c6af;// 0x250d00;
	static const int BODY_COLOR_NORMAL = 0x472f22;
}

Player::Player(Scene* sc)
	:Object		(sc)
	,fillFlag	(false)
	,keystop	(false)
	,isStop		(true)
	,pos		()
	,disp		(Vec2{0,0})
	,nowMove	(Vec2{0,0})
	,size		(PlayerConfig::BODY_SIZE)
	,hImage		(-1)
	,direction	(0)
	,moveAnim	(0)
{}
Player::~Player(){
	if(hImage>0)
		DeleteGraph(hImage);
}
void Player::Init() {
	Field* field = GetScene()->Invoke<Field>();
	assert(CheckClass<Field>());

	Vec2 startPos;
	startPos.x = field->GetPlayerStart().x;
	startPos.y = field->GetPlayerStart().y;

	pos = startPos;
#ifdef _DEBUG
#else
	BackOne* bo = GetScene()->Invoke<BackOne>();
	if (bo != nullptr) 
		bo->PushToPlayer(0, startPos);
#endif

	hImage = LoadGraph("data/texture/character.png");
	assert(hImage>0);
}
void Player::Update() {

	//入力受付
	Move();

	//位置変更
	disp.x		= pos.x * size + PlayerConfig::START_OFFSET_POSX;
	disp.y		= pos.y * size + PlayerConfig::START_OFFSET_POSY;

	//移動アニメーション(位置
	nowMove.x	= DownDistance(nowMove.x);
	nowMove.y	= DownDistance(nowMove.y);

	isStop		= nowMove.x == 0 && nowMove.y == 0;

	//移動アニメーション(画像
	int x		= nowMove.x<0?-nowMove.x:nowMove.x;
	int y		= nowMove.y<0?-nowMove.y:nowMove.y;
	moveAnim	= (x+ y)/10%3;

}
void Player::Draw(){

	int radius = size /2;
	radius -= 1;//ここにマイナスをいれると間が空く

	Vec2 square = disp + nowMove;
	if (isStop) 
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255*0.65f));
	
	
	//キャラ画像
	int widthSize	= 96/3;
	int heightSize	= 128/4;

	DrawRectExtendGraph(square.x - radius, square.y - radius, square.x + radius
		, square.y + radius, widthSize*moveAnim, heightSize*direction, widthSize,heightSize,hImage,true);

	if (isStop) 
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	printfDx("\n"											);
	printfDx("WASD または 十字キーで 移動\n"				);
	printfDx("\n"											);
	printfDx("TAB  または バックスペースキーで 1つ戻る\n"	);

#ifdef _DEBUG
//本体　
	int color = BODY_COLOR_NORMAL;
	fillFlag ? color = BODY_COLOR_NORMAL : color= BODY_COLOR_KEY_INPUT;

	DrawBox(square.x- radius, square.y- radius, 
			square.x+ radius, square.y+ radius, color,true);

	//装飾用（枠
	DrawBox(square.x- radius, square.y- radius,
			square.x+ radius, square.y+ radius,0x302833,false);

	//装飾用（文字
	StrDraw(square								);
	printfDx("nowmove. x= %d\n",nowMove.x		);
	printfDx("nowmove. y= %d\n",nowMove.y		);
	printfDx("disp. x=    %d\n",disp.x			);
	printfDx("disp. y=    %d\n",disp.y			);
	printfDx("pos. x=     %d\n",pos.x			);
	printfDx("pos. y=     %d\n",pos.y			);
#endif
}

void Player::Reset(){
	fillFlag	= false;
	keystop		= false;
	isStop		= true;
	direction	= 0;
	moveAnim	= 0;
	nowMove.x	= 0;
	nowMove.y	= 0;

	Field* field = GetScene()->Invoke<Field>();
	assert(field != nullptr);

	pos		= field->GetPlayerStart();
	disp.x	= pos.x*PlayerConfig::BODY_SIZE+PlayerConfig::START_OFFSET_POSX;
	disp.y	= pos.y*PlayerConfig::BODY_SIZE+PlayerConfig::START_OFFSET_POSY;
}

void Player::Move(){
	bool upKey		= CheckHitKey(KEY_INPUT_W)		|| CheckHitKey(KEY_INPUT_UP)	;
	bool downKey	= CheckHitKey(KEY_INPUT_S)		|| CheckHitKey(KEY_INPUT_DOWN)	;
	bool leftKey	= CheckHitKey(KEY_INPUT_A)		|| CheckHitKey(KEY_INPUT_LEFT)	;
	bool rightKey	= CheckHitKey(KEY_INPUT_D)		|| CheckHitKey(KEY_INPUT_RIGHT)	;
	bool backKey	= CheckHitKey(KEY_INPUT_TAB)	|| CheckHitKey(KEY_INPUT_BACK)	;
	bool allKey		= upKey || downKey || rightKey  || leftKey||backKey;
#ifdef _DEBUG
	fillFlag = allKey||CheckHitKey(KEY_INPUT_SPACE);
	isStop = true;
#endif

	if (upKey&&!keystop && isStop) {
		direction = static_cast<int>(PlayerDirection::back);
		Player::MoveWhere({0,-1});
	}

	if (downKey && !keystop && isStop) {
		direction = static_cast<int>(PlayerDirection::front);
		Player::MoveWhere({ 0,1 });
	}

	if (leftKey && !keystop && isStop) {
		direction = static_cast<int>(PlayerDirection::left);
		Player::MoveWhere({ -1,0 });
	}

	if(rightKey && !keystop && isStop) {
		direction = static_cast<int>(PlayerDirection::right);
		Player::MoveWhere({ 1,0 });
	}
#ifdef _DEBUG
#else
	if (backKey && !keystop ) {
		BackOne* bo = GetScene()->Invoke<BackOne>();
		MoveBox* mb = GetScene()->Invoke<MoveBox>();

		if (bo != nullptr) {
			pos = bo->GetToPlayerPos();
			direction = bo->GetToPlayerDir();
		}

		if (mb != nullptr)
			mb->MoveBack();
	}
#endif
	keystop = allKey;
}

int Player::DownDistance(int _obj){
	if (_obj < -MOVE_SPEED) {
		_obj += MOVE_SPEED;
	}
	else if (_obj > MOVE_SPEED) {
		_obj -= MOVE_SPEED;
	}
	else {
		return 0;
	}

	return _obj;
}

void Player::MoveWhere(Vec2 _vec){

	Vec2 fPos			= pos + _vec;

	Field* field		= GetScene()->Invoke<Field>();
	if (!CheckClass<Field>())
		return;

	MoveBox* moveBox	= GetScene()->Invoke<MoveBox>();
	if (!CheckClass<MoveBox>())
		return;

#ifdef _DEBUG
#else
	BackOne* backOne	= GetScene()->Invoke<BackOne>();
	assert(CheckClass<BackOne>());
#endif
	if (field->GetfieldInside(fPos) == 1) 
		return;

	Vec2 minnus		= { -1,-1 }					;//x y に-1が入ってる
	Vec2 vSize		= { size,size }				;//x y にsizeが入ってる
	const int index = moveBox->GetIndex(fPos)	;
	if (index != -1) {
		//二つ上を見る
		Vec2 f2Pos		= fPos + _vec;
		const int index2= moveBox->GetIndex(f2Pos);
		if (index2 != -1)
			return;

		//全て大丈夫な場合
		const Vec2 bPos	= moveBox->GetPos(index);
		if(bPos==fPos){

			if (field->GetfieldInside(f2Pos) == 1)
				return;

#ifdef _DEBUG 
#else
			backOne->PushToPlayer(direction,pos);
			moveBox->PushPoss();
#endif
			//動き
			moveBox->MoveWhere(index, _vec)	;
			pos		+= _vec					;
			_vec	*= minnus * vSize		;
			nowMove += _vec					;

		}
		else {
#ifdef _DEBUG 
#else
			backOne->PushToPlayer(direction, pos);
			moveBox->PushPoss();
#endif
			//動き
			pos		+= _vec;
			nowMove  = _vec * minnus * vSize;
		}
	}
	else {
#ifdef _DEBUG 
#else
		backOne->PushToPlayer(direction, pos);
		moveBox->PushPoss();
#endif
		//動き
		pos		+= _vec;
		nowMove  = _vec * minnus * vSize;
	}
}

void Player::StrDraw(Vec2 square){
	int fontS=GetFontSize();

	SetFontSize(48);
	
	DrawFormatString(square.x-10,square.y-24,0xdddddd,"P");
	
	SetFontSize(fontS);
}
