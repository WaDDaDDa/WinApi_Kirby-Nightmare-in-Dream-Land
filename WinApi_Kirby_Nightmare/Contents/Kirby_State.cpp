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
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
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

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Fly);
		return;
	}
}



void Kirby::WalkUpdate(float _Delta)
{
	DirCheck();

	float Speed = 500.0f;
	float4 PlayerPos = GetPos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	MovePos = float4::ZERO;


	if (true == GameEngineInput::IsPress('A') && Dir == KirbyDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(KirbyState::Idle);
	}

	// �÷��̾� �̵�
	AddPos(MovePos);
	PlayerPos = GetPos();
	// ī�޶����̵�   �÷��̾ �����̸� ī�޶� �̵��Ѵ�.

	//if (MovePos != float4::ZERO)
	//{
	//	GetLevel()->GetMainCamera()->AddPos(MovePos);
	//}

	// ������ ȭ��â ������ �ѱ���ϸ� ī�޶� �����δ�.
	//if (420 < PlayerPos.iX() - CameraPos.iX() || 20 > PlayerPos.iX() - CameraPos.iX())
	//{
	//	GetLevel()->GetMainCamera()->AddPos({ MovePos.X, 0 });
	//}

	//if (0 < CameraPos.iY() - PlayerPos.iY() || -480 > CameraPos.iY() - PlayerPos.iY())
	//{
	//	GetLevel()->GetMainCamera()->AddPos({ 0, MovePos.Y });
	//}

}

void Kirby::JumpUpdate(float _Delta)
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

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Idle);
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