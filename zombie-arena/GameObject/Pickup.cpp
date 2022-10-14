#include "Pickup.h"
#include "Player.h"
#include "../Framework/ResourceMgr.h"

Pickup::Pickup()
	: type(Types::None), value(0), player(nullptr)
{

}

Pickup::~Pickup()
{

}

void Pickup::SetPlayer(Player* p)
{
	player = p;
}

void Pickup::SetType(Types t)
{
	ResourceMgr* resMgr = RESOURCE_MGR;

	type = t;
	switch (type)
	{
	case Pickup::Types::None:
		// 텍스처 클리어
		break;
	case Pickup::Types::Ammo:
		SetTexture(*resMgr->GetTexture("graphics/ammo_pickup.png"));
		SetOrigin(Origins::MC);
		break;
	case Pickup::Types::Health:
		SetTexture(*resMgr->GetTexture("graphics/health_pickup.png"));
		SetOrigin(Origins::MC);
		break;
	}
}

void Pickup::SetValue(int v)
{
	value = v;
}

void Pickup::Update(float dt)
{
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->OnPickupItem(this);	
		SetActive(false);
	}
}
