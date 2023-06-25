#include "Portal.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Portal::Portal()
{

}

Portal::~Portal()
{

}

void Portal::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("KirbyIdel.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Hub World\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Portal.bmp"), 5, 10);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlackDoor.bmp"), 1, 1);
		}
	}

	Door = CreateRenderer(RenderOrder::Stage);
	Door->CreateAnimation("CloseDoor", "Portal.bmp", 0, 0, 0.1f, false);
	Door->CreateAnimation("BlackDoor", "BlackDoor.bmp", 0, 0, 0.1f, false);
	Door->SetTexture("Blank.bmp");
	Door->SetScaleRatio(4.0f);
	Door->ChangeAnimation("CloseDoor");

	BodyCollision = CreateCollision(CollisionOrder::Portal);
	BodyCollision->SetCollisionScale(BodyCollisionScale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Portal::Update(float _Delta)
{

}
