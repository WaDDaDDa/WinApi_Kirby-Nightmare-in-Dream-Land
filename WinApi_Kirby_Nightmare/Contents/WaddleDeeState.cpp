#include "WaddleDee.h"


void WaddleDee::IdleStart()
{
	ChangeAnimationState("Idle");
}

void WaddleDee::IdleUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(WaddleDeeState::Walk);
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
	}
}

void WaddleDee::HitStart()
{
	ChangeAnimationState("Hit");
}

void WaddleDee::HitUpdate(float _Delta)
{
	if (GetLiveTime() >= 3.0f)
	{
		Death();
	}

	AddPos({0.2f, 0.0f});
}