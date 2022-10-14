#include "UiMgr.h"

UiMgr::UiMgr(Scene* scene)
	:parentScene(scene)
{
}

UiMgr::~UiMgr()
{
}

void UiMgr::Init()
{
	Object::Init();
	for (auto uiObj : uiObjList)
	{
		uiObj->Init();
	}
}

void UiMgr::Release()
{
	Object::Release();
	for (auto uiObj : uiObjList)
	{
		uiObj->Release();
	}
}

void UiMgr::Reset()
{
	Object::Reset();
	for (auto uiObj : uiObjList)
	{
		uiObj->Reset();
	}
}

void UiMgr::SetPos(const Vector2f& pos)
{
	Vector2f delta = pos - position;
	for (auto uiObj : uiObjList)
	{
		uiObj->Translate(delta);
	}
	position = pos;
}

void UiMgr::Update(float dt)
{
	if (!enabled)
		return;

	for (auto uiObj : uiObjList)
	{
		if (uiObj->GetActive())
		{
			uiObj->Update(dt);
		}
	}
}

void UiMgr::Draw(RenderWindow& window)
{
	if (!enabled)
		return;

	for (auto uiObj : uiObjList)
	{
		if (uiObj->GetActive())
		{
			uiObj->Draw(window);
		}
	}
}
