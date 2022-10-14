#pragma once
#include <list>
#include "Object.h"

class Pickup;

class ItemGenerator : public Object
{
protected:
	float createIntervalMin;
	float createIntervalMax;
	float createInterval;
	float createTimer;
	int createMax;
	float radius;
	std::list<Pickup*> itemList;

public:
	ItemGenerator();
	virtual ~ItemGenerator();

	virtual void Reset();
	virtual void Update(float dt) override;

	virtual void Generate();
};

