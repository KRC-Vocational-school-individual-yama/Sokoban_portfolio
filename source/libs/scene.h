#pragma once
#include<list>

class Object;

class Scene {
public:
	Scene()					;
	virtual ~Scene()		;
	virtual void Update()	;
	virtual void Draw()		;

	/// <summary>
	/// �I�u�W�F�N�g�̐���
	/// <para>���X�g�ɒǉ���
	/// �A�h���X��Ԃ�</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	Object* Create() {
		C* tempObject= new C(this);
		objectList.emplace_back(tempObject);
		return tempObject;
	}

	/// <summary>
	/// <para>�I�u�W�F�N�g�̌Ăяo��</para>
	/// <para>�����N���X���ォ��1����Ă���</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	C* Invoke() {
		for (auto it = objectList.begin(); it != objectList.end(); ++it) {
			C* obj = dynamic_cast<C*>(*it);
			if (obj != nullptr) 
				return obj;
		}
		return nullptr;
	}

	/// <summary>
	/// <para>�I�u�W�F�N�g�̔j��</para>
	/// <para>�����N���X���ォ��1����</para>
	/// </summary>
	/// <typeparam name="C"></typeparam>
	template<class C>
	void Destroy() {
		for (auto it = objectList.begin(); it != objectList.end(); ) {
			C* obj = dynamic_cast<C*>(*it);
			if (obj != nullptr) {
				delete obj;
				it=objectList.erase(it);
				return;
			}
			else {
				++it;
			}
		}
	}

private:
	void AllDestroy();//�S�ẴI�u�W�F�N�g���폜

	std::list<Object*>objectList;//�I�u�W�F�N�g�L�^�p

};
