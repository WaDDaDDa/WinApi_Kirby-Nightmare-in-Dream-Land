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

void Kirby::BreathInStart()
{
	ChangeAnimationState("BreathIn");
}

// IsDown���� Ű�� �޾Ƽ� State�� ü�����ϰ� �Ǹ� 
// ������Ʈ�� ���� �ൿ�� ���ϴ� �ܰ�.
void Kirby::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) == Color)
	{
		ChangeState(KirbyState::Falling);
		return;
	}

	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('D'))
	{
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
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Run);
		return;
	}


}



void Kirby::WalkUpdate(float _Delta)
{
	GroundCheck(_Delta);

	DirCheck();

	Movement(_Delta);

	// ����
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::Jump);
		return;
	}
	// ���
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		ChangeState(KirbyState::Idle);
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) == Color)
	{
		ChangeState(KirbyState::Falling);
		return;
	}
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
		ChangeState(KirbyState::Falling);
		return;
	}

	MovePos = { 0.0f , -JumpPower * _Delta, };

	AddPos(MovePos);
	// �ִϸ��̼� ��� ����
	if (GetLiveTime() >= 0.6f)
	{
		ChangeState(KirbyState::JumpTurn);
		return;
	}

	// ������ �̵�
	Movement(_Delta);

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::BreathIn);
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
	Movement(_Delta);
	GravityReset();

	if (GetLiveTime() >= 0.2f)
	{
		ChangeState(KirbyState::Falling);
		
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::BreathIn);
		return;
	}
}

void Kirby::FallingUpdate(float _Delta)
{
	DirCheck();
	GroundCheck(_Delta);

	Movement(_Delta);

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::BreathIn);
		return;
	}

	// ���� ������ �⺻����.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) != Color)
	{
		CameraFocus();
		GravityReset();
		ChangeState(KirbyState::FallingEnd);
		return;
	}

}

void Kirby::FallingEndUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('S')
		|| true == GameEngineInput::IsPress('D'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::Jump);
		return;
	}

}

void Kirby::RunUpdate(float _Delta)
{

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::FlyUpdate(float _Delta)
{
	CameraFocus();
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

	if (true == GameEngineInput::IsPress('X'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::BreathInUpdate(float _Delta)
{
	DirCheck();
	MovePos = { 0.0f , -JumpPower / 10 * _Delta, };
	AddPos(MovePos);
	Movement(_Delta);
	CameraFocus();

	if (GetLiveTime() >= 0.35f)
	{
		ChangeState(KirbyState::Fly);
		GravityReset();
		return;
	}
}
