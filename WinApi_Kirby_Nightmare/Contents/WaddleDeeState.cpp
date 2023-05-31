#include "WaddleDee.h"
#include <GameEngineCore/GameEngineRenderer.h>

void WaddleDee::IdleStart()
{
	ChangeAnimationState("Idle");
}

void WaddleDee::IdleUpdate(float _Delta)
{
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
		MainRenderer->Off();
	}
	else
	{
		MainRenderer->On();
	}

}

void WaddleDee::HitStart()
{
	ChangeAnimationState("Hit");
}

void WaddleDee::HitUpdate(float _Delta)
{
	float4 MoveDir = Actor->GetPos() - GetPos();
	MoveDir.Normalize();
	AddPos(MoveDir * 800.0f* _Delta);

	std::vector<GameEngineCollision*> _Col;
	//플레이어 몸통과 충돌.
	if (true == DeathCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			Death();
		}
	}
}