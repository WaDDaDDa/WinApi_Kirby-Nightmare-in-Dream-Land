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
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_AirAttackEffect.bmp"), 6, 1);
		}
		{ // LeftAnimation ����
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_AirAttackEffect.bmp"), 6, 1);
		}
	}

	Renderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation ����
		Renderer->CreateAnimation("Left_AirAttack", "Left_AirAttackEffect.bmp", 0, 5, 0.2f, true);
	}
	{ // RightAnimation ����
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

	// 1�ʵ� ����
	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}

}