#include "scene.h"
#include"object.h"

Scene::Scene()
	:objectList()
{}
Scene::~Scene(){
	AllDestroy();
}

void Scene::Update(){
	for (auto& object : objectList) {
		//初期化フラグが立っていれば初期化
		if (object->GetInitFlag()) {
			object->Init();
			object->SetInitFlag(false);
		}

		//オブジェクトの更新
		object->Update();
	}
}
void Scene::Draw(){
	//オブジェクトの描画
	for (auto& object : objectList)
		object->Draw();
}

void Scene::AllDestroy(){

	if (objectList.empty())
		return;
	
	//全てを削除
	for (auto it = objectList.begin(); it != objectList.end(); ) {
		Object*& object = *it;
		if (nullptr != object) {
			delete object;
			it=objectList.erase(it);
		}
	}
}
