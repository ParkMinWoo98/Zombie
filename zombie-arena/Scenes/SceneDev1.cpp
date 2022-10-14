#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/Player.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/VertexArrayObj.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/ItemGenerator.h"
#include "../Ui/UiDev1Mgr.h"

void OnCreateBullet(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);

	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet.png"));
	bullet->SetZombieList(scene->GetZombieList());
	bullet->SetBackground(scene->GetBackground());
	bullet->Init();
}

SceneDev1::SceneDev1() : Scene(Scenes::Dev1)
{

}

SceneDev1::~SceneDev1()
{
	
}

void SceneDev1::Init()
{
	Release();

	uiMgr = new UiDev1Mgr(this);
	uiMgr->Init();

	CreateBackground(26, 15, 50.f, 50.f);

	Vector2i centerPos = FRAMEWORK->GetWindowSize() / 2;
	background->SetPos({ 0, 0 });
	background->SetOrigin(Origins::MC);

	player = new Player();
	player->SetName("Player");
	player->SetTexture(*GetTexture("graphics/player.png"));
	player->SetBulletPool(&bullets);
	player->SetBackground(background);
	objList.push_back(player);

	bullets.OnCreate = OnCreateBullet;
	bullets.Init();

	ItemGenerator* itemGen = new ItemGenerator();
	itemGen->SetName("ItemGenerator");
	AddGameObj(itemGen);

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneDev1::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}

	bullets.Release();

	Scene::Release();
	player = nullptr;
}

void SceneDev1::Enter()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);	// 마우스 커서를 윈도우 밖으로 안 나가게 하는 함수
	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f centerPos(size.x * 0.5f, size.y * 0.5f);

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	player->SetPos( { 0, 0 });
	CreateZombies(100);
}

void SceneDev1::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);

	auto it = zombies.begin();
	while (it != zombies.end())
	{
		objList.remove(*it);
		delete* it;
		it = zombies.erase(it);
	}
	player->Reset();
	bullets.Reset();

	FindGameObj("ItemGenerator")->Reset();

	uiMgr->Reset();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(player->GetPos());

	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
		return;
	}
	bullets.Update(dt);

	uiMgr->Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);

	const auto& bulletList = bullets.GetUseList();
	for (auto bullet : bulletList)
	{
		bullet->Draw(window);
	}
	uiMgr->Draw(window);
}

void SceneDev1::CreateBackground(int cols, int rows, float quadWidth, float quadHeight)
{
	if (background == nullptr)
	{
		background = new VertexArrayObj();
		background->SetTexture(GetTexture("graphics/background_sheet.png"));
		objList.push_back(background);
	}

	Vector2f startPos = background->GetPos();
	VertexArray& va = background->GetVA();
	va.clear();
	va.setPrimitiveType(Quads);
	va.resize(cols * rows * 4);
	Vector2f currPos = startPos;

	Vector2f offsets[4] = {
		{ 0, 0 },
		{ quadWidth, 0 },
		{ quadWidth, quadHeight },
		{ 0, quadHeight },
	};

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if ((i == 0 || i == rows - 1) || (j == 0 || j == cols - 1))
			{
				texIndex = 3;
			}

			int quadIndex = i * cols + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.y += quadHeight * texIndex;
			}
			currPos.x += 50;
		}
		currPos.x = startPos.x;
		currPos.y += 50;
	}
}

void SceneDev1::CreateZombies(int count)
{
	auto winSize = FRAMEWORK->GetWindowSize();
	FloatRect rect(200.f, 200.f, winSize.x - 400.f, winSize.y - 400.f);

	Vector2f point;

	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = new Zombie();
		zombie->SetType(
			(Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));

		zombie->Init(player);

		point.x = Utils::RandomRange(-1.0f, 1.0f);
		point.y = Utils::RandomRange(-1.0f, 1.0f);
		point = Utils::Normalize(point);
		point *= Utils::RandomRange(0.f, 500.f);
		zombie->SetPos(point);
		zombie->SetBackground(background);

		objList.push_back(zombie);
		zombies.push_back(zombie);
	}
}

VertexArrayObj* SceneDev1::GetBackground() const
{
	return background;
}
