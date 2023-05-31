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

void Kirby::DownIdleStart()
{
	ChangeAnimationState("DownIdle");
}

void Kirby::TackleStart()
{
	ChangeAnimationState("Tackle");
}

void Kirby::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Kirby::JumpStart()
{
	SetGravityVector(float4::UP * 1.4f);
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
	GravityReset();
	ChangeAnimationState("Fly");
}

void Kirby::BreathInStart()
{
	ChangeAnimationState("BreathIn");
}

void Kirby::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void Kirby::AttackStart()
{
	AttackCollision->On();
	ChangeAnimationState("Attack");
}

// IsDown���� Ű�� �޾Ƽ� State�� ü�����ϰ� �Ǹ� 
// ������Ʈ�� ���� �ൿ�� ���ϴ� �ܰ�.
void Kirby::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) == Color && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)))
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
		ChangeState(KirbyState::DownIdle);
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::AttackStart);
		return;
	}
}

void Kirby::DownIdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('D'))
	{
		ChangeState(KirbyState::Walk);
		return;
	}

	if (true == GameEngineInput::IsUp('S'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Tackle);
		return;
	}
}

void Kirby::TackleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	
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
	//CameraFocus();
}

void Kirby::WalkUpdate(float _Delta)
{
	DirCheck();

	GroundCheck(_Delta);
	Movement(_Delta);
	static float Deley = 0;
	// ����
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::Jump);
		return;
	}
	// ����
	if (true == GameEngineInput::IsDown('Z'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::AttackStart);
		return;
	}

	// ���
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		ChangeState(KirbyState::Idle);
	}
	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN + LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN + RightCheck);

	if ((RGB(255, 255, 255) == Color && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)))
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
	Gravity(_Delta);
	DirCheck();
	// �Ӹ��� üũ
	float4 UpCheck = { 0 , -64 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		// ü���� ����
		ChangeState(KirbyState::Falling);
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown('Z'))
	{
		GravityReset();
		//MovePos *= 0.8f;
		ChangeState(KirbyState::AttackStart);
		return;
	}

	//MovePos = { 0.0f , -JumpPower * _Delta};
	//AddPos(MovePos);
	
	// �ִϸ��̼� ��� ����
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(KirbyState::JumpTurn);
		return;
	}
	float4 Vet = GetGravityVector();
	// ������ �̵�
	Movement(_Delta);

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::BreathIn);
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

	// ����
	if (true == GameEngineInput::IsDown('Z'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::AttackStart);
		return;
	}

	// ���� ������ �⺻����.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) != Color || LeftColor != RGB(255, 255, 255) || RightColor != RGB(255, 255, 255)))

	{
		MovePos = float4::ZERO;
		//CameraFocus();
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
	DirCheck();
	Gravity(_Delta);

	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
	unsigned int CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
	unsigned int CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);

	// üũ�� ����ϳ���  ����� �ƴ϶�� ��ĭ�ø��� �ݺ��Ѵ�.
	while (CheckColor != RGB(255, 255, 255) || CheckLeftColor != RGB(255, 255, 255) || CheckRightColor != RGB(255, 255, 255))
	{
		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
		CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
		CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);
		AddPos(float4::UP);
	}

	float4 UpCheck = { 0 , -80 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		SetGravityVector(float4::UP * 0.5f);
		//MovePos = { 0.0f , -200 * _Delta, };
		//AddPos(MovePos);
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
	//CameraFocus();

	if (GetLiveTime() >= 0.35f)
	{
		ChangeState(KirbyState::Fly);
		return;
	}
}

void Kirby::AttackStartUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (Dir == KirbyDir::Left)
	{
		//CameraFocus();
		CheckPos = { -40.0f, -40.0f };
		// ������
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
		}
		AddPos(MovePos);
	}
	else if (Dir == KirbyDir::Right)
	{
		//CameraFocus();
		CheckPos = { 40.0f, -40.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
		}
		AddPos(MovePos);
	}

	if (GetLiveTime() >= 0.3f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}

	if (true == GameEngineInput::IsUp('Z'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	
}

void Kirby::AttackUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (KirbyDir::Left == Dir)
	{
		AttackCollision->SetCollisionPos({ -AttackCollisionPos.X , AttackCollisionPos.Y });
	}
	else if (KirbyDir::Right == Dir)
	{
		AttackCollision->SetCollisionPos(AttackCollisionPos);
	}

	if (true == GameEngineInput::IsUp('Z'))
	{
		AttackCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}
	
}
