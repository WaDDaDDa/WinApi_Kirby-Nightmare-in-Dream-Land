#include "BurningKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>

void BurningKirby::AttackStartUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.6f)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 TackleSpeed = { 2.0f , 0.0f };
	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(-TackleSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(TackleSpeed);
	}
}

void BurningKirby::AttackUpdate(float _Delta)
{

	if (GetLiveTime() >= 0.6f)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 TackleSpeed = { 1.0f , 0.0f };
	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(-TackleSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(TackleSpeed);
	}
}
