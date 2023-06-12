#include "AirAttack.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"


AirAttack::AirAttack()
{

}

AirAttack::~AirAttack()
{

}

void AirAttack::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Left_AirAttackEffect.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_AirAttackEffect.bmp"), 6, 1);
		}
		{ // LeftAnimation 셋팅
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_AirAttackEffect.bmp"), 6, 1);
		}
	}

	Renderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("Left_AirAttack", "Left_AirAttackEffect.bmp", 0, 5, 0.2f, true);
	}
	{ // RightAnimation 생성
		Renderer->CreateAnimation("Right_AirAttack", "Right_AirAttackEffect.bmp", 0, 5, 0.2f, true);
	}
	Renderer->ChangeAnimation("Right_AirAttack");
	Renderer->SetScaleRatio(4.0f);

}

void AirAttack::Update(float _Delta)
{
	if (KirbyDir::Left == MainKirby->GetDir())
	{
		Dir = float4::LEFT;
		Renderer->ChangeAnimation("Left_AirAttack");
	}
	else if (KirbyDir::Right == MainKirby->GetDir())
	{
		Dir = float4::RIGHT;
	}
	AddPos(Dir * _Delta * Speed);

	// 1초뒤 데스
	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}

}