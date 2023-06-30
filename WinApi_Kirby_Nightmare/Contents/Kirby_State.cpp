#include "Kirby.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "AirAttack.h"
#include "BurningKirby.h"
#include "Star.h"
#include "MainHubLevel.h"

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
	SoundEffect = GameEngineSound::SoundPlay("song173.wav");
	TackleCollision->On();
	Speed = TackleSpeed;
	ChangeAnimationState("Tackle");
}

void Kirby::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Kirby::JumpStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song115.wav");
	SetGravityVector(float4::UP * JumpPower);
	ChangeAnimationState("Jump");
}
void Kirby::JumpTurnStart()
{
	ChangeAnimationState("JumpTurn");
}

void Kirby::JumpAttackStartStart()
{
	ChangeAnimationState("JumpAttackStart");
}

void Kirby::JumpAttackStart()
{
	AttackCollision->On();
	if (KirbyDir::Left == GetDir())
	{
		LeftChargeRenderer->On();
	}
	else if (KirbyDir::Right == GetDir())
	{
		RightChargeRenderer->On();
	}
	ChangeAnimationState("JumpAttack");
}

void Kirby::FallingStart()
{
	ChangeAnimationState("Falling");
}
void Kirby::FallingEndStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song528.wav");
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
	SetGravityVector(float4::UP * 200.0f);
	ChangeAnimationState("BreathIn");
}

void Kirby::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void Kirby::AttackStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song103.wav", 500);
	AttackCollision->On();
	if (KirbyDir::Left == GetDir())
	{
		LeftChargeRenderer->On();
	}
	else if (KirbyDir::Right == GetDir())
	{
		RightChargeRenderer->On();
	}
	ChangeAnimationState("Attack");
}

void Kirby::ChargeStart()
{
	ChangeAnimationState("Charge");
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
	SoundEffect = GameEngineSound::SoundPlay("song115.wav");
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
	SoundEffect = GameEngineSound::SoundPlay("song528.wav");
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

void Kirby::DamageStart()
{
	SoundEffect.Stop();
	SoundEffect = GameEngineSound::SoundPlay("song111.wav");
	DamageHP();
	BodyCollision->Off();
	AttackCollision->Off();
	TackleCollision->Off();
	ChangeAnimationState("Damage");
}

void Kirby::FatDamageStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song111.wav");
	DamageHP();
	BodyCollision->Off();
	ChangeAnimationState("FatDamage");
}

void Kirby::OpenDoorStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song222.wav");
	BodyCollision->Off();
	ChangeAnimationState("OpenDoor");
}

void Kirby::DieReadyStart()
{
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0.0f);
	GameEngineTime::MainTimer.SetTimeScale(RenderOrder::Play, 0.0f);

	ChangeAnimationState("DieReady");
}

void Kirby::DieStart()
{
	CameraValue = false;
	SetGravityVector(float4::UP * 1000.0f);
	ChangeAnimationState("Die");
}

void Kirby::OverStart()
{
	Life -= 1;
	HP = 6;
	ChangeAnimationState("Over");
}

// IsDown���� Ű�� �޾Ƽ� State�� ü�����ϰ� �Ǹ� 
// ������Ʈ�� ���� �ൿ�� ���ϴ� �ܰ�.
void Kirby::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	//unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	//unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) == Color/* && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)*/))
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

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Tackle);
		return;
	}
}

void Kirby::TackleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (KirbyDir::Left == Dir)
	{
		TackleCollision->SetCollisionPos(float4{ -TackleCollisionPos.X , TackleCollisionPos.Y});
	}
	else if (KirbyDir::Right == Dir)
	{
		TackleCollision->SetCollisionPos(TackleCollisionPos);
	}
	
	if (GetLiveTime() >= 0.6f)
	{
		Speed = NormalSpeed;
		TackleCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}
	float4 MovePos1 = { Speed * _Delta, 0.0f };
	if (KirbyDir::Left == Dir)
	{
		CheckPos = LeftCheckPos;
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(-MovePos1);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = RightCheckPos;
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(MovePos1);
	}

	std::vector<GameEngineCollision*> _Col;
	if (true == TackleCollision->Collision(CollisionOrder::MonsterBody
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();
			float4 TackleEnd = float4::ZERO;
			if (GetDir() == KirbyDir::Left)
			{
				TackleEnd = float4::UP * 400.0f + float4::RIGHT * 200.0f;
			}
			else if (GetDir() == KirbyDir::Right)
			{
				TackleEnd = float4::UP * 400.0f + float4::LEFT * 200.0f;
			}
			SetGravityVector(TackleEnd);
			Speed = NormalSpeed;
			ChangeState(KirbyState::Falling);
			return;
		}
	}

}

void Kirby::WalkUpdate(float _Delta)
{
	DirCheck();

	GroundCheck(_Delta);
	Movement2(_Delta);
	// ����
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::Jump);
		return;
	}
	// ����
	if (true == GameEngineInput::IsDown('X'))
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
	// �Ӹ��� üũ�� �Ͼ���� �ƴ϶�� Falling���� ������ȯ. = �ٸ������� �ִٸ� Falling
	// �Ӹ��� üũ�� ����̸� Falling,  �������̸� ���.  �̷������� �ϸ� ����ϴ� ������ ������������.
	float4 UpCheck = { 0 , -64 };
	float4 RightUpCheck = { 26 , -64 };
	float4 LeftUpCheck = { -26 , -64 };

	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	unsigned int RightColorCheck = GetGroundColor(RGB(255, 255, 255), RightUpCheck);
	unsigned int LeftColorCheck = GetGroundColor(RGB(255, 255, 255), LeftUpCheck);
	if (ColorCheck == RGB(0, 255, 0) || RightColorCheck == RGB(0, 255, 0) || LeftColorCheck == RGB(0, 255, 0))
	{
		// ü���� ����
		SetGravityVector(float4::ZERO);
		ChangeState(KirbyState::Falling);
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown('X'))
	{
		GravityReset();
		ChangeState(KirbyState::JumpAttackStart);
		return;
	}
		// �ִϸ��̼� ��� ����
	if (GetGravityVector().iY() >= float4::ZERO.iY())
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
}

void Kirby::JumpAttackStartUpdate(float _Delta)
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

	if (true == GameEngineInput::IsUp('X'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::JumpAttackUpdate(float _Delta)
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
		RightChargeRenderer->Off();
		LeftChargeRenderer->Off();
		ChangeState(KirbyState::Idle);
		return;
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == AttackCollision->Collision(CollisionOrder::DeathBody
		, _Col
		, CollisionType::CirCle // ��
		, CollisionType::CirCle // ���
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			ChangeState(KirbyState::Charge);
			return;
		}
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

	if (true == GameEngineInput::IsDown('X'))
	{
		GravityReset();
		ChangeState(KirbyState::JumpAttackStart);
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
	Gravity(_Delta);
	//GroundCheck(_Delta);

	Movement(_Delta);

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::BreathIn);
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::JumpAttackStart);
		return;
	}

	// ���� ������ �⺻����.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	//unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	//unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if (RGB(255, 255, 255) != Color/* || LeftColor != RGB(255, 255, 255) || RightColor != RGB(255, 255, 255)*/)
	{
		MovePos = float4::ZERO;
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
// �޸��� ����
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

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	//unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	//unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	// �÷��̾� ��ġ�� ����̸� �߷��ۿ�.
	// ��� ����̸� �����̴�.
	if (RGB(255, 255, 255) == Color /*&& LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)*/)
	{
		//Gravity(_Delta);
	}
	else // �������� �ƴϴ� = ��������ִ�.
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
		//unsigned int CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
		//unsigned int CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);

		// üũ�� ����ϳ���  ����� �ƴ϶�� ��ĭ�ø��� �ݺ��Ѵ�.
		while (CheckColor != RGB(255, 255, 255))// || CheckLeftColor != RGB(255, 255, 255) || CheckRightColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			//CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
			//CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);
			AddPos(float4::UP);
		}
		GravityReset();
	}

	// õ�� üũ
	float4 UpCheck = { 0 , -80 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck == RGB(0, 255, 0))
	{
		while (ColorCheck != RGB(255,255,255))
		{
			UpCheck = UpCheck + float4::DOWN;
			ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
			AddPos(float4::DOWN);
		}
		//GravityReset();
		//SetGravityVector(-GetGravityVector());
		//return;
	}

	if (true == GameEngineInput::IsDown('F') || GameEngineInput::GetPressTime('F') >= 0.4f)
	{
		SoundEffect = GameEngineSound::SoundPlay("song120.wav");
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
	//Gravity(_Delta);
	DirCheck();
	Movement(_Delta);
	GroundCheck(_Delta);

	float4 UpCheck = { 0 , -80 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck == RGB(0, 255, 0))
	{
		//SetGravityVector(-GetGravityVector());
		while (RGB(0, 255, 0) != ColorCheck)
		{
			UpCheck.Y += 1;
			AddPos(UpCheck);
		}
	}

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
		SoundEffect.Stop();
		AttackCollision->Off();
		RightChargeRenderer->Off();
		LeftChargeRenderer->Off();
		ChangeState(KirbyState::Idle);
		return;
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == AttackCollision->Collision(CollisionOrder::DeathBody
		, _Col
		, CollisionType::CirCle // ��
		, CollisionType::CirCle // ���
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			ChangeState(KirbyState::Charge);
			return;
		}
	}
}

void Kirby::ChargeUpdate(float _Delta)
{
	GroundCheck(_Delta);

	std::vector<GameEngineCollision*> _Col;

	if (true == EatCollision->Collision(CollisionOrder::DeathBody
		, _Col
		, CollisionType::CirCle // ��
		, CollisionType::CirCle // ���
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeAbillity = Actor->GetAbillity();
			Actor->Death();
			AttackCollision->Off();
			RightChargeRenderer->Off();
			LeftChargeRenderer->Off();
			SoundEffect.Stop();
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
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::FatIdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	//unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	//unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) == Color))// && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)))
	{
		ChangeState(KirbyState::FatFalling);
		return;
	}
	// �̵�
	if (true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsPress('D'))
	{
		ChangeState(KirbyState::FatWalk);
		return;
	}
	// ��Ű��
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Swallow);
		return;
	}
	// ����
	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(KirbyState::FatJump);
		return;
	}
	// ����
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
	// ����
	if (true == GameEngineInput::IsDown('F'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::FatJump);
		return;
	}
	// ����
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::StarOut);
		return;
	}
	// ��Ű��
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Swallow);
		return;
	}

	// ���
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		ChangeState(KirbyState::FatIdle);
	}
	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
	//unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN + LeftCheck);
	//unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN + RightCheck);

	if ((RGB(255, 255, 255) == Color))// && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255)))
	{
		ChangeState(KirbyState::FatFalling);
		return;
	}
}

void Kirby::FatJumpUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();
	// �Ӹ��� üũ
	float4 UpCheck = { 0 , -64 };
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);
	if (ColorCheck != RGB(255, 255, 255))
	{
		// ü���� ����
		SetGravityVector(float4::ZERO);
		ChangeState(KirbyState::FatFalling);
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown('X'))
	{
		GravityReset();
		ChangeState(KirbyState::StarOut);
		return;
	}
	// �ִϸ��̼� ��� ����
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(KirbyState::FatJumpTurn);
		return;
	}
	// ������ �̵�
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

	// ����
	if (true == GameEngineInput::IsDown('X'))
	{
		MovePos = float4::ZERO;
		ChangeState(KirbyState::StarOut);
		return;
	}

	// ���� ������ �⺻����.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	//unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	//unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	if ((RGB(255, 255, 255) != Color))// || LeftColor != RGB(255, 255, 255) || RightColor != RGB(255, 255, 255)))
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
	if (GetLiveTime() >= 0.2f)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

//����
void Kirby::SwallowUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.4f)
	{
		// �������� ��ü����
		if (Abillity::Burning == ChangeAbillity)
		{
			ChangeKirby(Abillity::Burning);
		}
		else if (Abillity::Spark == ChangeAbillity)
		{
			ChangeKirby(Abillity::Spark);
		}
		else if (Abillity::Sword == ChangeAbillity)
		{
			ChangeKirby(Abillity::Sword);
		}
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::DamageUpdate(float _Delta)
{
	if (0 == HP)
	{
		ChangeState(KirbyState::DieReady);
		return;
	}

	GroundCheck(_Delta);
	float4 MoveDir = float4::ZERO;
	if (KirbyDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (KirbyDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}

	// ������
	if (Dir == KirbyDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// ������
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == KirbyDir::Left)
	{
		CheckPos = { 40.0f, -40.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}

	MoveDir.Normalize();
	AddPos(MoveDir * 200.0f * _Delta);

	if (GetLiveTime() >= 0.4f)
	{
		ImmuneValue = true;
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::FatDamageUpdate(float _Delta)
{
	float4 MoveDir = float4::ZERO;
	if (KirbyDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (KirbyDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	MoveDir.Normalize();
	AddPos(MoveDir * 200.0f * _Delta);

	if (GetLiveTime() >= 0.4f)
	{
		ImmuneValue = true;
		ChangeState(KirbyState::FatIdle);
		return;
	}
}

void Kirby::OpenDoorUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::DieReadyUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(KirbyState::Die);
		return;
	}
}

void Kirby::DieUpdate(float _Delta)
{
	Gravity(_Delta);
	if (GetLiveTime() >= 2.0f)
	{
		ChangeState(KirbyState::Over);
		return;
	}
}

void Kirby::OverUpdate(float _Delta)
{
	Gravity(_Delta);
	if (GetLiveTime() >= 2.0f)
	{
		return;
	}
}
