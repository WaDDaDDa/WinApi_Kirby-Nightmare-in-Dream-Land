#include "Kirby.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"

// ������ �̹����� ���� �������ְ� �̹����� �׿� �°� �����ǰ� �����鼭 update�� �Ͼ��.

// Start�� ������ �̹��� �ִϸ��̼��� ���� ������ִ� �ܰ�.
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


// IsDown���� Ű�� �޾Ƽ� State�� ü�����ϰ� �Ǹ� 
// ������Ʈ�� ���� �ൿ�� ���ϴ� �ܰ�.
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

	// �߷� ���� 
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
// ���� �ٰ� ���� �ְ��������� JumpTurn�ִϸ��̼� ������ְ� 
// �������� Falling�ִϸ��̼� ������ְ� 
// ���� ������ �����ִϸ��̼�.
void Kirby::JumpUpdate(float _Delta)
{
	DirCheck();
	GroundCheck(_Delta);
	static bool Value = false;
	// �ϴ��� �ð����� ������. 
	if (1.5f <= GetLiveTime() && Value == false)
	{
		/*ChangeState(KirbyState::JumpTurn);*/
		ChangeAnimationState("JumpTurn");
		//ResetLiveTime();
		MovePos = float4::ZERO;
		Value = true;
		return;
	}

	if (2.5f <= GetLiveTime())
	{
		/*ChangeState(KirbyState::JumpTurn);*/
		ChangeAnimationState("Falling");
		
		MovePos = float4::ZERO;
		//ChangeState(KirbyState::Idle);
		//ResetLiveTime();
		return;
	}



	if (true == GameEngineInput::IsPress('A') && Dir == KirbyDir::Left)
	{
		CheckPos = { -24.0f, -24.0f };

		MovePos = { -Speed * _Delta, 0.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			return;
		}
		AddPos(MovePos);
		CameraFocus();
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		CheckPos = { 24.0f, -24.0f };

		MovePos = { Speed * _Delta, 0.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			return;
		}
		AddPos(MovePos);
		CameraFocus();
	}

	MovePos = {  0.0f , -JumpPower * _Delta, };

	AddPos(MovePos);
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