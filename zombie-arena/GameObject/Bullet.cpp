#include "Bullet.h"
#include "../Framework/Utils.h"
#include "Zombie.h"
#include "VertexArrayObj.h"

Bullet::Bullet()
	: dir(), speed(0.f), range(0.f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Fire(const Vector2f& pos, const Vector2f& dir, float speed, float range)
{
	sprite.setRotation(Utils::Angle(dir));
	SetPos(pos);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
}

void Bullet::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Bullet::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();
}

void Bullet::Release()
{
	SpriteObj::Release();
}

void Bullet::Reset()
{
	dir = { 1, 0 };
	speed = 0.f;
	range = 0.f;
	sprite.setRotation(0.f);
	SetPos({ 0, 0 });

	SpriteObj::Reset();
}

void Bullet::Update(float dt)
{
	SpriteObj::Update(dt);
	//SetPos(position + dir * dt * speed);

	Translate(dir * dt * speed);
	range -= Utils::Magnitude(dir * dt * speed);

	if (range < 0)
	{
		SetActive(false);
	}
	else
	{
		for (Zombie* zombie : *zombies)
		{
			if (zombie->GetActive())
			{
				if (GetGlobalBounds().intersects(zombie->GetGlobalBounds()))
				{
					zombie->OnHitBullet(this);
					SetActive(false);
					break;
				}
			}
		}
	}

	float border = 50.f;
	FloatRect wallBound = background->GetGlobalBounds();
	Vector2f pos;
	pos.x = Utils::Clamp(position.x,
		wallBound.left + border,
		wallBound.left + wallBound.width - border);
	pos.y = Utils::Clamp(position.y,
		wallBound.top + border,
		wallBound.top + wallBound.height - border);
	if (pos != position)
	{
		SetActive(false);
	}
}

void Bullet::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}
