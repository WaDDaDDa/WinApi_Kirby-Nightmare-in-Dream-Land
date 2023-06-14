#include "Kirby.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "AirAttack.h"
#include "BurningKirby.h"
#include "Star.h"

// 랜더할 이미지를 먼저 설정해주고 이미지는 그에 맞게 랜더되고 있으면서 update가 일어난다.

// Start는 렌더할 이미지 애니메이션을 먼저 등록해주는 단계.
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
	SetGravityVector(float4::UP * JumpPower);
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

void Kirby::StarInStart()
{
	ChangeAnimationState("StarIn");
}

void Kirby::StarOutStart()
{
	ChangeAnimationState("StarOut");
}

void Kirby::FatIdleStart()
{
	ChangeAnimationState("FatIdle");
}

void Kirby::FatWalkStart()
{
	ChangeAnimationState("FatWalk");
}

void Kirby::FatJumpStart()
{
	SetGravityVector(float4::UP * JumpPower * 0.8f);
	ChangeAnimationState("FatJump");
}

void Kirby::FatJumpTurnStart()
{
	ChangeAnimationState("FatJumpTurn");
}

void Kirby::FatFallingStart()
{
	ChangeAnimationState("FatFalling");
}

void Kirby::FatFallingEndStart()
{
	ChangeAnimationState("FatFallingEnd");
}

void Kirby::BreathOutStart()
{
	ChangeAnimationState("BreathOut");
}

void Kirby::SwallowStart()
{
	ChangeAnimationState("Swallow");
}

// IsDown으로 키를 받아서 State를 체인지하게 되면 
// 업데이트는 실제 행동을 행하는 단계.
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

	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::AttackStart);
		return;
	}
	// 플레이어 변경 가능함.
	//if (true == GameEngineInput::IsDown('E'))
	//{
	//	float4 PrevPos = MainPlayer->GetPos();
	//	MainPlayer->Death();
	//	MainPlayer = GetLevel()->CreateActor<BurningKirby>();
	//	MainPlayer->SetPos(PrevPos);
	//	MainPlayer->SetGroundTexture("MainHupDebug.bmp");
	//	return;
	//}
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
}

void Kirby::WalkUpdate(float _Delta)
{
	DirCheck();

	GroundCheck(_Delta);
	Movement(_Delta);
	// 점프
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::Jump);
		return;
	}
	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::AttackStart);
		return;
	}

	// 대기
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
// 점프 뛰고 점프 최고점찍으면 JumpTurn애니메이션 출력해주고 
// 떨어질때 Falling애니메이션 출력해주고 
// 땅에 닿을때 뿌직애니메이션.
void Kirby::JumpUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();
	// 머리위 체크
	float4 UpCheck = { 0 , -64 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		// 체인지 폴링
		SetGravityVector(float4::ZERO);
		ChangeState(KirbyState::Falling);
		return;
	}

	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		GravityReset();
		ChangeState(KirbyState::AttackStart);
		return;
	}
		// 애니메이션 출력 변경
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(KirbyState::JumpTurn);
		return;
	}
	// 점프중 이동
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

	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::AttackStart);
		return;
	}

	// 땅에 닿으면 기본상태.
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
// 달리기 보류
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

	// 체크중 어느하나라도  흰색이 아니라면 한칸올리기 반복한다.
	while (CheckColor != RGB(255, 255, 255) || CheckLeftColor != RGB(255, 255, 255) || CheckRightColor != RGB(255, 255, 255))
	{
		//GravityReset();  없으면 Fly상태일때 떨어지면 심한가속, 있으면 땅위에서 두들현상.
		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
		CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
		CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);
		AddPos(float4::UP);
		GravityReset();
	}

	float4 UpCheck = { 0 , -80 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		GravityReset();
		return;
	}

	if (true == GameEngineInput::IsDown('F') || GameEngineInput::GetPressTime('F') >= 0.4f)
	{
		GameEngineInput::ResetPressTime('F');
		SetGravityVector(float4::UP * JumpPower * 0.5f);
	}

	Movement(_Delta);

	if (true == GameEngineInput::IsPress('X'))
	{
		AirAttack* MainAttack = GetLevel()->CreateActor<AirAttack>();
		MainAttack->SetPos(GetPos());
		MainAttack->SetKirby(this);
		MainAttack->DirCheck();
		ChangeState(KirbyState::BreathOut);
		return;
	}
}

void Kirby::BreathInUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();
	SetGravityVector(float4::UP * 0.3f);
	Movement(_Delta);

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
		// 벽판정
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

	if (true == GameEngineInput::IsUp('X'))
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

	if (true == GameEngineInput::IsUp('X'))
	{
		AttackCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == BodyCollision->Collision(CollisionOrder::MonsterBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
			AttackCollision->Off();
			ChangeState(KirbyState::StarIn);
			return;
		}
	}
}

void Kirby::StarInUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.3f)
	{
		ChangeState(KirbyState::FatIdle);
		return;
	}
}

void Kirby::StarOutUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.25f)
	{
		Star* StarAttack = GetLevel()->CreateActor<Star>();
		StarAttack->SetPos(GetPos());
		StarAttack->SetKirby(this);
		StarAttack->DirCheck();
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::FatIdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) == Color && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)))
	{
		ChangeState(KirbyState::FatFalling);
		return;
	}
	// 이동
	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('D'))
	{
		ChangeState(KirbyState::FatWalk);
		return;
	}
	// 삼키기
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Swallow);
		return;
	}
	// 점프
	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::FatJump);
		return;
	}
	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::StarOut);
		return;
	}
}

void Kirby::FatWalkUpdate(float _Delta)
{
	DirCheck();

	GroundCheck(_Delta);
	Movement(_Delta);
	// 점프
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::FatJump);
		return;
	}
	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::StarOut);
		return;
	}
	// 삼키기
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Swallow);
		return;
	}

	// 대기
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		ChangeState(KirbyState::FatIdle);
	}
	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN + LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN + RightCheck);

	if ((RGB(255, 255, 255) == Color && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)))
	{
		ChangeState(KirbyState::FatFalling);
		return;
	}
}

void Kirby::FatJumpUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();
	// 머리위 체크
	float4 UpCheck = { 0 , -64 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		// 체인지 폴링
		SetGravityVector(float4::ZERO);
		ChangeState(KirbyState::FatFalling);
		return;
	}

	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		GravityReset();
		ChangeState(KirbyState::StarOut);
		return;
	}
	// 애니메이션 출력 변경
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(KirbyState::FatJumpTurn);
		return;
	}
	// 점프중 이동
	Movement(_Delta);
}

void Kirby::FatJumpTurnUpdate(float _Delta)
{
	DirCheck();
	Movement(_Delta);
	GravityReset();

	if (GetLiveTime() >= 0.2f)
	{
		ChangeState(KirbyState::FatFalling);
		return;
	}
}

void Kirby::FatFallingUpdate(float _Delta)
{
	DirCheck();
	GroundCheck(_Delta);

	Movement(_Delta);

	// 공격
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::StarOut);
		return;
	}

	// 땅에 닿으면 기본상태.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) != Color || LeftColor != RGB(255, 255, 255) || RightColor != RGB(255, 255, 255)))

	{
		MovePos = float4::ZERO;
		GravityReset();
		ChangeState(KirbyState::FatFallingEnd);
		return;
	}
}

void Kirby::FatFallingEndUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::FatIdle);
		return;
	}

	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('S')
		|| true == GameEngineInput::IsPress('D'))
	{
		ChangeState(KirbyState::FatIdle);
		return;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::FatJump);
		return;
	}
}

void Kirby::BreathOutUpdate(float _Delta)
{
	DirCheck();
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::SwallowUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.4f)
	{
		ChangeState(KirbyState::Idle);

		float4 PrevPos = MainPlayer->GetPos();
		MainPlayer->Death();
		MainPlayer = GetLevel()->CreateActor<BurningKirby>();
		MainPlayer->SetPos(PrevPos);
		MainPlayer->SetGroundTexture(GetGroundTexture());
		return;
	}
}