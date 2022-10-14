#include "ItemGenerator.h"
#include "../Framework/Utils.h"
#include "Pickup.h"
#include "../Scenes/SceneMgr.h"

ItemGenerator::ItemGenerator()
	:createIntervalMin(2.f), createIntervalMax(3.f), createInterval(0.f), createTimer(0.f), createMax(3), radius(500.f)
{
}

ItemGenerator::~ItemGenerator()
{
}

void ItemGenerator::Reset()
{
	Object::Reset();

	itemList.clear();
	createTimer = 0.f;
	createInterval = Utils::RandomRange(createIntervalMin, createIntervalMax);
}

void ItemGenerator::Update(float dt)
{
	createTimer += dt;
	if (createTimer > createInterval)
	{
		int count = Utils::RandomRange(1, createMax + 1);
		for (int i = 0; i < count; ++i)
		{
			Generate();
		}

		createTimer = 0.f;
		createInterval = Utils::RandomRange(createIntervalMin, createIntervalMax);
	}
}

void ItemGenerator::Generate()
{
	Scene* scene = SCENE_MGR->GetCurrScene();	// ToDo: ¼öÁ¤

	Pickup::Types itemType = (Pickup::Types)Utils::RandomRange(0, (int)Pickup::Types::Count);

	Pickup* item = new Pickup();
	item->SetType(itemType);
	item->SetValue(10);
	item->SetPlayer((Player*)scene->FindGameObj("Player"));
	item->Init();

	Vector2f center = { 0, 0 };
	bool success = false;
	int count = 0;
	while (!success && count < 20)
	{
		success = true;
		Vector2f pos = center + Utils::RandomInCirclePoint() * radius;
		item->SetPos(pos);
		for (auto i : itemList)
		{
			if (i->GetActive() && item->GetGlobalBounds().intersects(i->GetGlobalBounds()))
			{
				success = false;
				++count;
			}
		}
	}
	if (success)
	{
		itemList.push_back(item);
		scene->AddGameObj(item);
	}
	else
	{
		delete item;
	}
}
