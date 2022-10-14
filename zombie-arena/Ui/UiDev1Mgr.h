#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class Scene;

class UiDev1Mgr : public UiMgr
{
protected:
	// SCORE
	string formatScore; // "SCORE: %d"
	TextObj* textScore;

	SpriteObj* cursor;

public:
	UiDev1Mgr(Scene* scene);
	virtual ~UiDev1Mgr();

	void SetScore(int score);

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

