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
	/// �����V�[���擾
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()				{ return myScene;}

	/// <summary>
	/// �������t���O�@�Q�b�^�[
	/// </summary>
	/// <param name="true	">����������</param>
	/// <param name="false	">���������Ȃ�</param>
	/// <returns></returns>
	bool GetInitFlag()				{ return init	;}

	/// <summary>
	/// �������t���O�@�Z�b�^�[
	/// </summary>
	/// <param name="_flag	">True�@or�@Flase</param>
	void SetInitFlag(bool _flag)	{ init = _flag	;}

	/// <summary>
	/// Invoke�̍�  nullptr �`�F�b�N�p
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <param name="true	">inClass</param>
	/// <param name="false	">nullptr</param>
	/// <returns></returns>
	template<class C>
	bool CheckClass();
private:
	Scene* myScene	;//�����V�[��
	bool init		;//�������t���O
};

template<class C>
bool Object::CheckClass(){
	if (GetScene()->Invoke<C>() != nullptr)
		return true;

	return false;
};