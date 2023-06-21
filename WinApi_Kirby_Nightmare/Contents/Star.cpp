#include "Star.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

Star::Star()
{

}

Star::~Star()
{

}

void Star::Start()
{

	Renderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("StarAttack", "Star.bmp", 0, 1, 0.2f, true);
		//Renderer->CreateAnimation("StarEffect", "StarEffects.bmp", 0, 3, 0.1f, true);
		Renderer->CreateAnimation("StarEffect", "Effect1.bmp", 0, 6, 0.05f, true);
	}
	Renderer->SetTexture("Star.bmp");
	Renderer->ChangeAnimation("StarAttack");
	Renderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Player);

	AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
	AttackCollision->SetCollisionScale(AttackCollisionScale);
	AttackCollision->SetCollisionType(CollisionType::CirCle);
}


void Star::DirCheck()
{
	if (KirbyDir::Left == MainKirby->GetDir())
	{
		AddPos(LeftAttackPos);
		Dir = float4::LEFT;
	}
	else if (KirbyDir::Right == MainKirby->GetDir())
	{
		AddPos(RightAttackPos);
		Dir = float4::RIGHT;
	}
}

void Star::Update(float _Delta)
{

	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	StateUpdate(_Delta);
}

void Star::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void Star::ChangeState(StarState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case StarState::Attack:
			AttackStart();
			break;
		case StarState::Effect:
			EffectStart();
			break;
		}
	}
}


void Star::StateUpdate(float _Delta)
{
	switch (State)
	{
	case StarState::Attack:
		return AttackUpdate(_Delta);
	case StarState::Effect:
		return EffectUpdate(_Delta);
	default:
		break;
	}
}


void Star::AttackStart()
{

}

void Star::AttackUpdate(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	// 1초뒤 데스
	if (2.0f < GetLiveTime())
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
			ChangeState(StarState::Effect);
			Dir = float4::ZERO;
		}
	}
}

void Star::EffectStart()
{

}

void Star::EffectUpdate(float _Delta)
{
	if (0.5f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}
}