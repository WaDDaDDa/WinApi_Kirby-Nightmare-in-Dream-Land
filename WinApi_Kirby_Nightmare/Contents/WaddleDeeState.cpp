#include "WaddleDee.h"
#include <GameEngineCore/GameEngineRenderer.h>

void WaddleDee::IdleStart()
{
	ChangeAnimationState("Idle");
}

void WaddleDee::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(WaddleDeeState::Walk);
		return;
	}
}

void WaddleDee::WalkStart()
{
	ChangeAnimationState("Walk");
}

void WaddleDee::WalkUpdate(float _Delta)
{
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 4.0f)
	{
		ChangeState(WaddleDeeState::Idle);
		return;
	}
}

void WaddleDee::HitReadyStart()
{
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void WaddleDee::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(WaddleDeeState::Hit);
		return;
	}

	static int Value = 1;
	Value *= -1;

	if (Value == 1)
	{
		//MainRenderer->Off();
	}
	else
	{
		//MainRenderer->On();
	}

}

void WaddleDee::HitStart()
{
	ChangeAnimationState("Hit");
}

void WaddleDee::HitUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = Actor->GetPos() - GetPos();
	MoveDir.Normalize();
	AddPos(MoveDir * 800.0f* _Delta);

	std::vector<GameEngineCollision*> _Col;
	//플레이어 몸통과 충돌.
	//if (true == DeathCollision->Collision(CollisionOrder::PlayerBody
	//	, _Col
	//	, CollisionType::CirCle // 나를 사각형으로 봐줘
	//	, CollisionType::CirCle // 상대도 사각형으로 봐줘
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		Actor = Collison->GetActor();
	//		Death();
	//	}
	//}
}

void WaddleDee::DamageStart()
{
	ChangeAnimationState("Damage");
}

void WaddleDee::DamageUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = float4::ZERO;
	if (WaddleDeeDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (WaddleDeeDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == WaddleDeeDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == WaddleDeeDir::Left)
	{
		CheckPos = { 40.0f, -40.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}

	MoveDir.Normalize();
	AddPos(MoveDir * 100.0f * _Delta);

	if (0.5f <= GetLiveTime())
	{
		ChangeState(WaddleDeeState::Effect);
		return;
	}
}

void WaddleDee::EffectStart()
{
	AddPos(CollisionPos);
	BodyCollision->Off();
	ChangeAnimationState("Effect");
}

void WaddleDee::EffectUpdate(float _Delta)
{
	GroundCheck(_Delta);
	GravityOff();
	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}
