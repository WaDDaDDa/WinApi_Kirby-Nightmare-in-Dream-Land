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

void Kirby::RunStart()
{
	ChangeAnimationState("Idle");
}


void Kirby::ShootStart()
{
	ChangeAnimationState("Shoot");
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
		ChangeState(KirbyState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::Shoot);
		return;
	}

}



void Kirby::RunUpdate(float _Delta)
{
	DirCheck();

	float Speed = 300.0f;
	float4 PlayerPos = GetPos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	MovePos = float4::ZERO;


	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D'))
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
	if (420 < PlayerPos.iX() - CameraPos.iX() || 20 > PlayerPos.iX() - CameraPos.iX())
	{
		GetLevel()->GetMainCamera()->AddPos({ MovePos.X, 0 });
	}

	if (0 < CameraPos.iY() - PlayerPos.iY() || -480 > CameraPos.iY() - PlayerPos.iY())
	{
		GetLevel()->GetMainCamera()->AddPos({ 0, MovePos.Y });
	}

}

void Kirby::ShootUpdate(float _Delta)
{

	Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
	NewBullet->Renderer->SetTexture("TestMonster1.Bmp");
	// ������ ǥ���ϴ� xy�� ũ�Ⱑ 1�̾�� �մϴ�.
	NewBullet->SetDir(float4::RIGHT);
	NewBullet->SetPos(GetPos());
	ChangeState(KirbyState::Idle);

}