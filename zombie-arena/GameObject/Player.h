#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"

enum class FireModes
{
	Manual,
	Semi,
	Auto,
};

class Bullet;
class Pickup;
class VertexArrayObj;
class Zombie;
class Scene;
class UiMgr;

class Player : public SpriteObj
{
protected:
	Vector2f look;	// 입력 방향, 단위 벡터
	Vector2f direction;	// 입력 방향, 단위 벡터
	float speed;	// 최대 속력
	float accelation;		// 가속도
	float deaccelation;		// 감속도

	Vector2f velocity; // 현재 속도

	VertexArrayObj* background;

	//
	ObjectPool<Bullet>* bulletPool;

	Scene* scene;
	UiMgr* uiMgr;

	int currentAmmo;
	int magazineSize;
	int ammo;

	bool isReloading;
	float reloadTime;
	float reloadTimer;

	float fireTimer;
	FireModes fireMode;
	int semiTotal;
	int semiCount;

	float intervalManual;
	float intervalSemiauto;
	float intervalAuto;
	bool isSemiFiring;

public:
	Player();
	virtual ~Player();
	
	void SetBulletPool(ObjectPool<Bullet>* ptr);
	void SetBackground(VertexArrayObj* bk);

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire();
	void Reload();

	void OnPickupItem(Pickup* item);
	void OnHitZombie(Zombie* zombie);
};

