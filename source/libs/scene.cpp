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
		//�������t���O�������Ă���Ώ�����
		if (object->GetInitFlag()) {
			object->Init();
			object->SetInitFlag(false);
		}

		//�I�u�W�F�N�g�̍X�V
		object->Update();
	}
}
void Scene::Draw(){
	//�I�u�W�F�N�g�̕`��
	for (auto& object : objectList)
		object->Draw();
}

void Scene::AllDestroy(){

	if (objectList.empty())
		return;
	
	//�S�Ă��폜
	for (auto it = objectList.begin(); it != objectList.end(); ) {
		Object*& object = *it;
		if (nullptr != object) {
			delete object;
			it=objectList.erase(it);
		}
	}
}
