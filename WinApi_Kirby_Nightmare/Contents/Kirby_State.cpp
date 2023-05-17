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

void Kirby::RunStart()
{
	ChangeAnimationState("Idle");
}


void Kirby::ShootStart()
{
	ChangeAnimationState("Shoot");
}


// IsDown으로 키를 받아서 State를 체인지하게 되면 
// 업데이트는 실제 행동을 행하는 단계.
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

	// 플레이어 이동
	AddPos(MovePos);
	PlayerPos = GetPos();
	// 카메라의이동   플레이어가 움직이면 카메라도 이동한다.

	//if (MovePos != float4::ZERO)
	//{
	//	GetLevel()->GetMainCamera()->AddPos(MovePos);
	//}

	// 윈도우 화면창 범위를 넘기려하면 카메라가 움직인다.
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
	// 방향을 표현하는 xy는 크기가 1이어야 합니다.
	NewBullet->SetDir(float4::RIGHT);
	NewBullet->SetPos(GetPos());
	ChangeState(KirbyState::Idle);

}