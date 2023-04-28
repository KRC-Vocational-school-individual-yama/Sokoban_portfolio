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
	/// 選んだステージを設定
	/// </summary>
	/// <param name="_num	">ステージナンバー</param>
	void SetSelected(int _num) { selected = _num; }
	/// <summary>
	/// 選んだステージを取得
	/// </summary>
	/// <returns></returns>
	int GetSelected() { return selected; }
private:
	int selected;//選んだステージ
};