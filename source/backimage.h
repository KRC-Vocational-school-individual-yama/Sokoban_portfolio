#pragma once
#include"libs/object.h"
class BackImage :public Object{
public:
	BackImage(Scene* sc)		;
	~BackImage()		override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

private:
	int hImage					;//‰æ‘œƒnƒ“ƒhƒ‹
};