#pragma once
#include "Scene.h"

class Object;

class SceneDev2 : public Scene
{
protected:
	Object* obj1;
	Object* obj2;

public:
	SceneDev2();
	virtual ~SceneDev2();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

