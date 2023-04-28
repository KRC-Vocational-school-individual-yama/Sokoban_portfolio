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
	/// オブジェクトの生成
	/// <para>リストに追加し
	/// アドレスを返す</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	Object* Create() {
		C* tempObject= new C(this);
		objectList.emplace_back(tempObject);
		return tempObject;
	}

	/// <summary>
	/// <para>オブジェクトの呼び出し</para>
	/// <para>同じクラスを上から1つ取ってくる</para>
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
	/// <para>オブジェクトの破棄</para>
	/// <para>同じクラスを上から1つ消す</para>
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
	void AllDestroy();//全てのオブジェクトを削除

	std::list<Object*>objectList;//オブジェクト記録用

};
