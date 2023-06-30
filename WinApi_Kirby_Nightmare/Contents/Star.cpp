#include "Star.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

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
		Renderer->CreateAnimation("StarEffect", "StarEffects.bmp", 0, 3, 0.1f, true);
		//Renderer->CreateAnimation("StarEffect", "Effect1.bmp", 0, 6, 0.1f, true);
	}
	Renderer->SetTexture("Star.bmp");
	Renderer->ChangeAnimation("StarAttack");
	Renderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Player);

	AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
	AttackCollision->SetCollisionScale(AttackCollisionScale);
	AttackCollision->SetCollisionType(CollisionType::CirCle);

	BossAttackCollision = CreateCollision(CollisionOrder::BossAttack);
	BossAttackCollision->SetCollisionScale(AttackCollisionScale);
	BossAttackCollision->SetCollisionType(CollisionType::CirCle);

	SetPos(Kirby::GetMainPlayer()->GetPos());
	DirCheck();
	ChangeState(StarState::Attack);
	SoundEffect = GameEngineSound::SoundPlay("song105.wav");

}

void Star::DirCheck()
{
	if (KirbyDir::Left == Kirby::GetMainPlayer()->GetDir())
	{
		AddPos(LeftAttackPos);
		Dir = float4::LEFT;
	}
	else if (KirbyDir::Right == Kirby::GetMainPlayer()->GetDir())
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

	Renderer->ChangeAnimation(AnimationName);
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

	ResetLiveTime();

	State = _State;
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
	ChangeAnimationState("StarAttack");
}

void Star::AttackUpdate(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	// 1초뒤 데스
	if (1.5f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			ChangeState(StarState::Effect);
		}
	}

	if (Dir == float4::LEFT)
	{
		float4 CheckPos = float4{ -40.0f, 0.0f };
		// 벽판정
		unsigned int WallColor = Kirby::GetMainPlayer()->GetGroundTexture()->GetColor(RGB(255, 255, 255), GetPos() + CheckPos);
		if (WallColor != RGB(255, 255, 255))
		{
			ChangeState(StarState::Effect);
			return;
		}
	}
	else if (Dir == float4::RIGHT)
	{
		float4 CheckPos = float4{ 40.0f, 0.0f };
		unsigned int WallColor = Kirby::GetMainPlayer()->GetGroundTexture()->GetColor(RGB(255, 255, 255), GetPos() + CheckPos);
		if (WallColor != RGB(255, 255, 255))
		{
			ChangeState(StarState::Effect);
			return;
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
			// Dir = float4::ZERO;
			ChangeState(StarState::Effect);
		}
	}

	if (true == BossAttackCollision->Collision(CollisionOrder::BossMonsterBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::Rect // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();
			// Dir = float4::ZERO;
			ChangeState(StarState::Effect);
		}
	}
}

void Star::EffectStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song215.wav");
	ChangeAnimationState("StarEffect");
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