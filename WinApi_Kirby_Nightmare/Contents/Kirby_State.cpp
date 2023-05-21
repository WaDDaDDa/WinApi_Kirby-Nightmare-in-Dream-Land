#include "Kirby.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"

// 랜더할 이미지를 먼저 설정해주고 이미지는 그에 맞게 랜더되고 있으면서 update가 일어난다.

// Start는 렌더할 이미지 애니메이션을 먼저 등록해주는 단계.
void Kirby::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Kirby::WalkStart()
{
	ChangeAnimationState("Walk");
}


void Kirby::JumpStart()
{
	ChangeAnimationState("Jump");
}

void Kirby::RunStart()
{
	ChangeAnimationState("Run");
}

void Kirby::FlyStart()
{
	ChangeAnimationState("Fly");
}


// IsDown으로 키를 받아서 State를 체인지하게 되면 
// 업데이트는 실제 행동을 행하는 단계.
void Kirby::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);


	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('W')
		|| true == GameEngineInput::IsPress('S')
		|| true == GameEngineInput::IsPress('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Jump);
		ResetLiveTime();
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Fly);
		return;
	}
}



void Kirby::WalkUpdate(float _Delta)
{

	// 중력 적용 
	GroundCheck(_Delta);

	DirCheck();

	MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == KirbyDir::Left)
	{
		CheckPos = { -24.0f, -24.0f };

		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		CheckPos = { 24.0f, -24.0f };

		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Jump);
		ResetLiveTime();
		return;
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(KirbyState::Idle);
	}

	if (GetWallCheck() != RGB(255, 255, 255))
	{
		return;
	}

	AddPos(MovePos);
}
// 점프 뛰고 점프 최고점찍으면 JumpTurn애니메이션 출력해주고 
// 떨어질때 Falling애니메이션 출력해주고 
// 땅에 닿을때 뿌직애니메이션.
void Kirby::JumpUpdate(float _Delta)
{
	DirCheck();
	GroundCheck(_Delta);

	MovePos = { 0.0f , -JumpPower * _Delta, };

	AddPos(MovePos);

	// 점프중 이동
	if (true == GameEngineInput::IsPress('A') && Dir == KirbyDir::Left)
	{
		CameraFocus();
		CheckPos = { -24.0f, -24.0f };

		MovePos = { -Speed * _Delta, 0.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			return;
		}
		AddPos(MovePos);
		
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		CameraFocus();
		CheckPos = { 24.0f, -24.0f };

		MovePos = { Speed * _Delta, 0.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
		}
		AddPos(MovePos);
		
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) != Color)
	{
		CameraFocus();
		ChangeState(KirbyState::Idle);
		return;
	}

}


void Kirby::RunUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::FlyUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Idle);
	}
}