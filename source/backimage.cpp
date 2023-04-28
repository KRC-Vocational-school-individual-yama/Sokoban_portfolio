#include "backimage.h"

#include"main/config.h"
#include"player.h"
#include"field.h"

BackImage::BackImage(Scene* sc)
	: Object(sc)
	, hImage(-1)
{}
BackImage::~BackImage(){
	if(hImage>0)
		DeleteGraph(hImage);
}
void BackImage::Init(){
	hImage=LoadGraph("data/texture/mapchip.png");
	assert(hImage > 0);
}
void BackImage::Update(){
}
void BackImage::Draw(){

#ifdef _DEBUG		//デバッグは背景無し
			
#else
	const int size = PlayerConfig::BODY_SIZE;

	for (int i = 0; i < SCREEN_WIDTH/size+2; i++) {//x
		for (int j = 0; j < SCREEN_HEIGHT/size+1; j++) {//y
			const int index = Field::IndexChange(i, j);
			const int halfSize = size / 2 ;//ここにマイナスを入れると間が空く
			
			const int x =  i * size;
			const int y =  j * size;

			Vec2 chip = { 4,3 };
			int widthSize = 256 / 8;
			int heightSize = 160 / 5;
			DrawRectExtendGraph(x - halfSize, y - halfSize, x + halfSize, y + halfSize
				, widthSize * chip.x, heightSize * chip.y, widthSize, heightSize, hImage, true);

		}
	}
#endif
}
