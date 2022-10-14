#include "UiDev1Mgr.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"
#include "../Scenes/SceneDev1.h"

UiDev1Mgr::UiDev1Mgr(Scene* scene)
	:UiMgr(scene), formatScore("SCORE: ")
{
}

UiDev1Mgr::~UiDev1Mgr()
{
}

void UiDev1Mgr::SetScore(int score)
{
	textScore->SetText(formatScore + to_string(score));
}

void UiDev1Mgr::Init()
{
	textScore = new TextObj();
	textScore->SetFont(*RESOURCE_MGR->GetFont("fonts/zombiecontrol.ttf"));
	textScore->GetSfmlText().setCharacterSize(75);
	textScore->GetSfmlText().setPosition({ 50, 50 });
	uiObjList.push_back(textScore);

	cursor = new SpriteObj();
	cursor->SetTexture(*RESOURCE_MGR->GetTexture("graphics/crosshair.png"));
	cursor->SetOrigin(Origins::MC);
	uiObjList.push_back(cursor);

	UiMgr::Init();
}

void UiDev1Mgr::Release()
{
	UiMgr::Release();
}

void UiDev1Mgr::Reset()
{
	UiMgr::Reset();
	SetScore(999999);
}

void UiDev1Mgr::Update(float dt)
{
	UiMgr::Update(dt);
	Vector2f worldMousePos = parentScene->ScreenToUiPos((Vector2i)InputMgr::GetMousePos());
	cursor->SetPos(worldMousePos);
}

void UiDev1Mgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}
