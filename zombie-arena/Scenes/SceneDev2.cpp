#include "SceneDev2.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"

SceneDev2::SceneDev2()
	: Scene(Scenes::Dev2)
{

}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
	obj1 = new Object();
	obj1->SetHitbox({ 0, 0, 100, 100 });
	obj1->SetPos({ 100, 100 });
	AddGameObj(obj1);

	obj2 = new Object();
	obj2->SetHitbox({ 0, 0, 100, 100 });
	obj2->SetPos({ 300, 100 });
	AddGameObj(obj2);

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneDev2::Release()
{
}

void SceneDev2::Enter()
{

}

void SceneDev2::Exit()
{
}

void SceneDev2::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}

	if (InputMgr::GetKeyDown(Keyboard::F1))
	{
		for (Object* obj : objList)
		{
			obj->SetDevMod(true);
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::F2))
	{
		for (Object* obj : objList)
		{
			obj->SetDevMod(false);
		}
	}

	Scene::Update(dt);
}

void SceneDev2::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
