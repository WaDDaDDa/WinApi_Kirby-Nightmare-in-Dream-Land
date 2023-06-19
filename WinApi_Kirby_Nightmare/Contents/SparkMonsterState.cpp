#include "SparkMonster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Bullet.h"
#include "Kirby.h"

void SparkMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void SparkMonster::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		int Value = GameEngineRandom::MainRandom.RandomInt(0, 1);
		float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;
		if (Posi <= 0 && SparkMonsterDir::Left == Dir)
		{
			ChangeState(SparkMonsterState::AttackStart);
			return;
		}
		if (Posi >= 0 && SparkMonsterDir::Right == Dir)
		{
			ChangeState(SparkMonsterState::AttackStart);
			return;
		}

		ChangeState(SparkMonsterState::Walk);
		return;
	}
}

void SparkMonster::WalkStart()
{
	AttackCollision->Off();
	SetGravityVector(float4::UP * JumpPower);
	ChangeAnimationState("Walk");
}

void SparkMonster::WalkUpdate(float _Delta)
{
	Gravity(_Delta);
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 0.5f)
	{
		ChangeState(SparkMonsterState::Idle);
		return;
	}
}

void SparkMonster::HitReadyStart()
{
	AttackCollision->Off();
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void SparkMonster::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(SparkMonsterState::Hit);
		return;
	}

	static int Value = 1;
	Value *= -1;

	if (Value == 1)
	{
		//MainRenderer->Off();
	}
	else
	{
		//MainRenderer->On();
	}

}

void SparkMonster::HitStart()
{
	AttackCollision->Off();
	ChangeAnimationState("Hit");
}

void SparkMonster::HitUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = Actor->GetPos() - GetPos();
	MoveDir.Normalize();
	AddPos(MoveDir * 800.0f * _Delta);

	std::vector<GameEngineCollision*> _Col;
	//플레이어 몸통과 충돌.
	//if (true == DeathCollision->Collision(CollisionOrder::PlayerBody
	//	, _Col
	//	, CollisionType::CirCle // 나를 사각형으로 봐줘
	//	, CollisionType::CirCle // 상대도 사각형으로 봐줘
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		Actor = Collison->GetActor();
	//		Death();
	//	}
	//}
}

void SparkMonster::DamageStart()
{
	AttackCollision->Off();
	ChangeAnimationState("Damage");
}

void SparkMonster::DamageUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = float4::ZERO;
	if (SparkMonsterDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (SparkMonsterDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == SparkMonsterDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == SparkMonsterDir::Left)
	{
		CheckPos = { 40.0f, -40.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}

	MoveDir.Normalize();
	AddPos(MoveDir * 100.0f * _Delta);

	if (0.5f <= GetLiveTime())
	{
		ChangeState(SparkMonsterState::Effect);
		return;
	}
}

void SparkMonster::EffectStart()
{
	AddPos(CollisionPos);
	BodyCollision->Off();
	ChangeAnimationState("Effect");
}

void SparkMonster::EffectUpdate(float _Delta)
{
	GroundCheck(_Delta);
	GravityOff();
	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}

void SparkMonster::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void SparkMonster::AttackStartUpdate(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		int Value = GameEngineRandom::MainRandom.RandomInt(0, 1);
		float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;
		if (Posi <= 0 && SparkMonsterDir::Left != Dir)
		{
			ChangeState(SparkMonsterState::Attack1);
			return;
		}
		if (Posi >= 0 && SparkMonsterDir::Right != Dir)
		{
			ChangeState(SparkMonsterState::Attack1);
			return;
		}

		switch (Value)
		{
		case 0:
			ChangeState(SparkMonsterState::Attack1);
			break;
		case 1:
			ChangeState(SparkMonsterState::Attack2);
			break;
		default:
			break;
		}
	}
}

// 불뿜기.
void SparkMonster::Attack1Start()
{
	AttackCollision->On();
	if (SparkMonsterDir::Left == GetDir())
	{
		LeftAttackRenderer->On();
		LeftAttack2Renderer->On();
	}
	else if (SparkMonsterDir::Right == GetDir())
	{
		RightAttackRenderer->On();
		RightAttack2Renderer->On();
	}

	ChangeAnimationState("Attack1");
}

void SparkMonster::Attack1Update(float _Delta)
{
	GroundCheck(_Delta);

	if (GetLiveTime() >= 1.0f)
	{
		LeftAttackRenderer->Off();
		LeftAttack2Renderer->Off();
		RightAttackRenderer->Off();
		RightAttack2Renderer->Off();
		AttackCollision->Off();
		ChangeState(SparkMonsterState::Walk);
		return;
	}

	if (SparkMonsterDir::Left == Dir)
	{
		AttackCollision->SetCollisionPos({ -AttackCollisionPos.X , AttackCollisionPos.Y });
	}
	else if (SparkMonsterDir::Right == Dir)
	{
		AttackCollision->SetCollisionPos(AttackCollisionPos);
	}
}

// 불 발사
void SparkMonster::Attack2Start()
{
	//Bullet* StarAttack = GetLevel()->CreateActor<Bullet>();
	//StarAttack->SetPos(GetPos() + float4{ 0,-40 });
	//StarAttack->SetMaster(this);
	//StarAttack->Init();

	ChangeAnimationState("Attack2");
}

void SparkMonster::Attack2Update(float _Delta)
{
	GroundCheck(_Delta);

	if (GetLiveTime() >= 0.5f)
	{
		LeftAttackRenderer->Off();
		LeftAttack2Renderer->Off();
		RightAttackRenderer->Off();
		RightAttack2Renderer->Off();
		AttackCollision->Off();
		ChangeState(SparkMonsterState::Walk);
		return;
	}

	if (SparkMonsterDir::Left == Dir)
	{
		AttackCollision->SetCollisionPos({ -AttackCollisionPos.X , AttackCollisionPos.Y });
	}
	else if (SparkMonsterDir::Right == Dir)
	{
		AttackCollision->SetCollisionPos(AttackCollisionPos);
	}
}