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
void Kirby::JumpTurnStart()
{
	ChangeAnimationState("JumpTurn");
}
void Kirby::FallingStart()
{
	ChangeAnimationState("Falling");
}
void Kirby::FallingEndStart()
{
	ChangeAnimationState("FallingEnd");
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
		|| true == GameEngineInput::IsPress('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeAnimationState("UnderIdle");
		return;
	}

	if (true == GameEngineInput::IsUp('S'))
	{
		ChangeAnimationState("Idle");
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
		CheckPos = { -40.0f, -40.0f };

		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };

		MovePos = { Speed * _Delta, 0.0f };
	}
	// ����
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::Jump);
		ResetLiveTime();
		return;
	}
	// ���
	if (MovePos == float4::ZERO)
	{
		ChangeState(KirbyState::Idle);
	}
	// ������
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

	// �Ӹ��� üũ
	float4 UpCheck = { 0 , -64 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		// ü���� ����
		return;
	}

	MovePos = { 0.0f , -JumpPower * _Delta, };

	AddPos(MovePos);
	// �ִϸ��̼� ��� ����
	if (GetLiveTime() >= 0.8f)
	{
		ChangeState(KirbyState::JumpTurn);
		//ChangeAnimationState("JumpTurn");
		ResetLiveTime();
		return;
	}

	// ������ �̵�
	Movement(_Delta);

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Fly);
		ResetLiveTime();
		return;
	}

	// ���� ������ �⺻����.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) != Color)
	{
		CameraFocus();
		GravityReset();
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::JumpTurnUpdate(float _Delta)
{
	DirCheck();
	GroundCheck(_Delta);

	Movement(_Delta);

	if (GetLiveTime() >= 0.4f)
	{
		ChangeState(KirbyState::Falling);
		//ChangeAnimationState("JumpTurn");
		ResetLiveTime();
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Fly);
		ResetLiveTime();
		return;
	}

}

void Kirby::FallingUpdate(float _Delta)
{

}

void Kirby::FallingEndUpdate(float _Delta)
{

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
	DirCheck();
	GroundCheck(_Delta);

	float4 UpCheck = { 0 , -80 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		return;
	}

	if (true == GameEngineInput::IsPress('F'))
	{
		GravityReset();
		MovePos = { 0.0f , -200 * _Delta, };
		AddPos(MovePos);
	}
	Movement(_Delta);

}