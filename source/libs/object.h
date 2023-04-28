#pragma once

#include"myDxLib.h"

#include<assert.h>
#include<string>
#include<vector>
#include<list>

class Scene;

class Object {
public:
	Object(Scene* sc)
		:myScene	(sc) 
		,init		(true)
	{}
	virtual ~Object()		=default;
	virtual void Init()		=0;
	virtual void Update()	=0;
	virtual void Draw()		=0;


	/// <summary>
	/// 所属シーン取得
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()				{ return myScene;}

	/// <summary>
	/// 初期化フラグ　ゲッター
	/// </summary>
	/// <param name="true	">初期化する</param>
	/// <param name="false	">初期化しない</param>
	/// <returns></returns>
	bool GetInitFlag()				{ return init	;}

	/// <summary>
	/// 初期化フラグ　セッター
	/// </summary>
	/// <param name="_flag	">True　or　Flase</param>
	void SetInitFlag(bool _flag)	{ init = _flag	;}

	/// <summary>
	/// Invokeの際  nullptr チェック用
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <param name="true	">inClass</param>
	/// <param name="false	">nullptr</param>
	/// <returns></returns>
	template<class C>
	bool CheckClass();
private:
	Scene* myScene	;//所属シーン
	bool init		;//初期化フラグ
};

template<class C>
bool Object::CheckClass(){
	if (GetScene()->Invoke<C>() != nullptr)
		return true;

	return false;
};