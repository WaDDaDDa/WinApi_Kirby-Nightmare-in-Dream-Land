#include "AirAttack.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

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
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirAttackCollision.bmp"), 2, 1);
		}
	}

	Renderer = CreateRenderer(RenderOrder::Effect);
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("Left_AirAttack", "Left_AirAttackEffect.bmp", 0, 5, 0.2f, true);
	}
	{ // RightAnimation 생성
		Renderer->CreateAnimation("Right_AirAttack", "Right_AirAttackEffect.bmp", 0, 5, 0.2f, true);
		Renderer->CreateAnimation("AirAttackCollision", "AirAttackCollision.bmp", 0, 1, 0.2f, true);
	}
	Renderer->SetTexture("Left_AirAttackEffect.bmp");
	Renderer->ChangeAnimation("Right_AirAttack");
	Renderer->SetScaleRatio(3.0f);

	SetOrder(UpdateOrder::Player);

	SoundEffect.SoundPlay("song114.wav");

	AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
	AttackCollision->SetCollisionScale(AttackCollisionScale);
	AttackCollision->SetCollisionType(CollisionType::CirCle);
}


void AirAttack::DirCheck()
{
	if (KirbyDir::Left == MainKirby->GetDir())
	{
		AddPos(LeftAttackPos);
		Renderer->ChangeAnimation("Left_AirAttack");
		Dir = float4::LEFT;
	}
	else if (KirbyDir::Right == MainKirby->GetDir())
	{
		AddPos(RightAttackPos);
		Renderer->ChangeAnimation("Right_AirAttack");
		Dir = float4::RIGHT;
	}
}

void AirAttack::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	AddPos(Dir * _Delta * Speed);
	Speed -= 300.0f * _Delta;

	// 1초뒤 데스
	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
			
		}
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();
			Renderer->SetRenderScale(float4{300,300});
			GameEngineSound::SoundPlay("song102.wav");
			Renderer->ChangeAnimation("AirAttackCollision");
		}
	}

}