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
	Vector2f look;	// �Է� ����, ���� ����
	Vector2f direction;	// �Է� ����, ���� ����
	float speed;	// �ִ� �ӷ�
	float accelation;		// ���ӵ�
	float deaccelation;		// ���ӵ�

	Vector2f velocity; // ���� �ӵ�

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
