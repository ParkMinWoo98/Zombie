#include "Zombie.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"
#include "VertexArrayObj.h"

const int Zombie::TotalTypes = 3;

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::Update(float dt)
{
	SpriteObj::Update(dt);

	dir = Utils::Normalize(player->GetPos() - GetPos());

	Translate(dir * speed* dt);

	float distance = Utils::Distance(player->GetPos(), GetPos());
	if (distance < speed * dt * 0.5f)
	{
		SetPos(player->GetPos());
	}
	else
	{
		float degree = atan2(dir.y, dir.x) * (180 / M_PI);
		sprite.setRotation(degree);
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
		SetPos(pos);
	}

	// 플레이어 충돌
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->OnHitZombie(this);
	}
}

void Zombie::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Zombie::Init(Player* player)
{
	this->player = player;
	SetOrigin(Origins::MC);

	SpriteObj::Init();
}

void Zombie::Reset()
{
	SpriteObj::Reset();

	dir = { 1, 0 };
	hp = maxHp;

	//dir = Utils::Normalize(player->GetPos() - GetPos());
	//float degree = atan2(dir.y, dir.x) * (180 / M_PI);
	//sprite.setRotation(degree);
	SetPos(position);
}

void Zombie::SetBackground(VertexArrayObj* bk)
{
	background = bk;
}

void Zombie::SetType(Types t)
{
	type = t;

	auto resMgr = RESOURCE_MGR;
	switch (type)
	{
	case Zombie::Types::Bloater:
		SetTexture(*resMgr->GetTexture("graphics/bloater.png"));
		speed = 40 ;
		maxHp = 100;
		break;
	case Zombie::Types::Chaser:
		SetTexture(*resMgr->GetTexture("graphics/chaser.png"));
		speed = 70;
		maxHp = 75;
		break;
	case Zombie::Types::Crawler:
		SetTexture(*resMgr->GetTexture("graphics/crawler.png"));
		speed = 20;
		maxHp = 50;
		break;
	}
}

Zombie::Types Zombie::GetType() const
{
	return type;
}

void Zombie::OnHitBullet(Bullet* bullet)
{
	// 체력 감소
	// 죽음
}
