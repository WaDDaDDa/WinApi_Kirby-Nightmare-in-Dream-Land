#include "Apple.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

Apple::Apple()
{

}

Apple::~Apple()
{

}

void Apple::Start()
{

	Renderer = CreateRenderer(RenderOrder::Play);
	Renderer->SetTexture("Blank.bmp");
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("AppleIdle", "WoodAtt.bmp", 0, 0, 0.2f, false);
		Renderer->CreateAnimation("AppleGround", "WoodAtt.bmp", 0, 0, 0.2f, false);
		Renderer->CreateAnimation("AppleFalling", "WoodAtt.bmp", 0, 7, 0.2f, true);
		Renderer->CreateAnimation("AppleHitReady", "WoodAtt.bmp", 0, 0, 0.1f, false);
		Renderer->CreateAnimation("AppleHit", "WoodAtt.bmp", 0, 0, 0.1f, false);
		Renderer->CreateAnimation("AppleEffect", "StarEffects.bmp", 0, 3, 0.1f, true);
		//Renderer->CreateAnimation("AppleEffect", "Effect1.bmp", 0, 6, 0.1f, true);
	}
	Renderer->ChangeAnimation("AppleIdle");
	Renderer->SetRenderPos(GetPos() + float4{0.0f, -40.0f});
	Renderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Player);

	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(BodyCollisionScale);
	BodyCollision->SetCollisionPos(float4{ 0.0f, -40.0f });
	BodyCollision->SetCollisionType(CollisionType::CirCle);

	DeathCollision = CreateCollision(CollisionOrder::DeathBody);
	DeathCollision->SetCollisionScale(DeathCollisionScale);
	DeathCollision->SetCollisionPos(float4{ 0.0f, -40.0f });
	DeathCollision->SetCollisionType(CollisionType::CirCle);
	DeathCollision->Off();

	SetPos(Kirby::GetMainPlayer()->GetPos());
	ChangeState(AppleState::Idle);
}

void Apple::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	std::vector<GameEngineCollision*> _Col;
	//플레이어 몸통과 충돌.
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			ChangeState(AppleState::Effect);
			return;
		}
	}
	//플레이어 공격과 충돌.
	if (true == BodyCollision->Collision(CollisionOrder::VacumAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::Rect // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			ChangeState(AppleState::HitReady);
			return;
		}
	}

	StateUpdate(_Delta);
}

void Apple::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	AnimationName += _StateName;

	CurState = _StateName;

	Renderer->ChangeAnimation(AnimationName);
}

void Apple::ChangeState(AppleState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case AppleState::Idle:
			IdleStart();
			break;
		case AppleState::Ground:
			GroundStart();
			break;
		case AppleState::Falling:
			FallingStart();
			break;
		case AppleState::Effect:
			EffectStart();
			break;
		case AppleState::HitReady:
			HitReadyStart();
			break;
		case AppleState::Hit:
			HitStart();
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}


void Apple::StateUpdate(float _Delta)
{
	switch (State)
	{
	case AppleState::Idle:
		return IdleUpdate(_Delta);
	case AppleState::Ground:
		return GroundUpdate(_Delta);
	case AppleState::Falling:
		return FallingUpdate(_Delta);
	case AppleState::Effect:
		return EffectUpdate(_Delta);
	case AppleState::HitReady:
		return HitReadyUpdate(_Delta);
	case AppleState::Hit:
		return HitUpdate(_Delta);
	default:
		break;
	}
}

void Apple::IdleStart()
{
	ChangeAnimationState("AppleIdle");
}
void Apple::IdleUpdate(float _Delta)
{
	if (2.0f < GetLiveTime())
	{
		ChangeState(AppleState::Falling);
	}
}

void Apple::GroundStart()
{
	ChangeAnimationState("AppleGround");
}
void Apple::GroundUpdate(float _Delta)
{
	if (4.0f < GetLiveTime())
	{
		ChangeState(AppleState::Effect);
	}
}

void Apple::FallingStart()
{
	ChangeAnimationState("AppleFalling");
}
void Apple::FallingUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (float4::ZERO == GetGravityVector())
	{
		ChangeState(AppleState::Ground);
		return;
	}
}

void Apple::EffectStart()
{
	ChangeAnimationState("AppleEffect");
}

void Apple::EffectUpdate(float _Delta)
{
	if (0.5f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}
}


void Apple::HitReadyStart()
{
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("AppleHitReady");
}

void Apple::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(AppleState::Hit);
		return;
	}
}

void Apple::HitStart()
{
	ChangeAnimationState("AppleHit");
}

void Apple::HitUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = Actor->GetPos() - GetPos();
	MoveDir.Normalize();
	AddPos(MoveDir * 800.0f * _Delta);

	if (GetLiveTime() >= 0.2f)
	{
		Death();
		return;
	}
}

