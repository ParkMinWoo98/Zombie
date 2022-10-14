#pragma once
#include "Scene.h"
#include <list>
#include "../Framework/ObjectPool.h"

class Player;
class VertexArrayObj;
class Zombie;
class Bullet;
class SpriteObj;

class SceneDev1 : public Scene
{
protected:
	VertexArrayObj* background;
	Player* player;
	list<Zombie*> zombies;
	SpriteObj* cursor;

	ObjectPool<Bullet> bullets;

public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateBackground(int cols, int rows, float quadWidth, float quadHeight);
	void CreateZombies(int count);

	list<Zombie*>* GetZombieList() { return &zombies; }
	VertexArrayObj* GetBackground() const;
};

