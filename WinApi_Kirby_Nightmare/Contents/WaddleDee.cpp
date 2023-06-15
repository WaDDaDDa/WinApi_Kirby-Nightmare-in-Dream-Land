#include "WaddleDee.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

WaddleDee::WaddleDee()
{

}

WaddleDee::~WaddleDee()
{

}

void WaddleDee::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("WaddleDeeLeft.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WaddleDeeLeft.bmp"), 3, 3);
		}

		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WaddleDeeRight.bmp"), 3, 3);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	{ // �ִϸ��̼� ����
		MainRenderer->CreateAnimation("WaddleDeeLeft_Idle", "WaddleDeeLeft.bmp", 2, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Walk", "WaddleDeeLeft.bmp", 1, 4, 0.3f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_HitReady", "WaddleDeeLeft.bmp", 5, 5, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Hit", "WaddleDeeLeft.bmp", 5, 5, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Damage", "WaddleDeeLeft.bmp", 5, 5, 0.1f, true);

		MainRenderer->CreateAnimation("WaddleDeeRight_Idle", "WaddleDeeRight.bmp", 2, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Walk", "WaddleDeeRight.bmp", 1, 4, 0.3f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_HitReady", "WaddleDeeRight.bmp", 5, 5, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Hit", "WaddleDeeRight.bmp", 5, 5, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Damage", "WaddleDeeRight.bmp", 5, 5, 0.1f, true);
	}

	{ // �浹ü ����
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionScale(CollisionScale);
		BodyCollision->SetCollisionPos(CollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);

		DeathCollision = CreateCollision(CollisionOrder::DeathBody);
		DeathCollision->SetCollisionScale(DeathCollisionScale);
		DeathCollision->SetCollisionPos(CollisionPos);
		DeathCollision->SetCollisionType(CollisionType::CirCle);
		DeathCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);
	SetAbillity(Abillity::Burning);
	SetPos(float4{ 500,360 });
	ChangeState(WaddleDeeState::Idle);
}

void WaddleDee::Update(float _Delta)
{
	StateUpdate(_Delta);
	GroundCheck(_Delta);

	std::vector<GameEngineCollision*> _Col;
	//�÷��̾� ����� �浹.
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];
			Actor = Collison->GetActor();
			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}
	//�÷��̾� ���ݰ� �浹.
	if (true == BodyCollision->Collision(CollisionOrder::VacumAttack
		, _Col
		, CollisionType::CirCle // ���� �浹ü ���
		, CollisionType::Rect // ����� �浹ü ���
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			ChangeState(WaddleDeeState::HitReady);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::PlayerAttack
		, _Col
		, CollisionType::CirCle // ���� �浹ü ���
		, CollisionType::CirCle // ����� �浹ü ���
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			Collison->Off();
			BodyCollision->Off();
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::SpecialAttack
		, _Col
		, CollisionType::CirCle // ���� �浹ü ���
		, CollisionType::Rect // ����� �浹ü ���
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			BodyCollision->Off();
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}


}

void WaddleDee::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WaddleDeeState::Idle:
		return IdleUpdate(_Delta);
	case WaddleDeeState::Walk:
		return WalkUpdate(_Delta);
	case WaddleDeeState::HitReady:
		return HitReadyUpdate(_Delta);
	case WaddleDeeState::Hit:
		return HitUpdate(_Delta);
	case WaddleDeeState::Damage:
		return DamageUpdate(_Delta);
	case WaddleDeeState::Effect:
		return EffectUpdate(_Delta);
	default:
		break;
	}
}

void WaddleDee::ChangeState(WaddleDeeState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case WaddleDeeState::Idle:
			IdleStart();
			break;
		case WaddleDeeState::Walk:
			WalkStart();
			break;
		case WaddleDeeState::HitReady:
			HitReadyStart();
			break;
		case WaddleDeeState::Hit:
			HitStart();
			break;
		case WaddleDeeState::Damage:
			DamageStart();
			break;
		case WaddleDeeState::Effect:
			EffectStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void WaddleDee::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case WaddleDeeDir::Right:
		AnimationName = "WaddleDeeRight_";
		break;
	case WaddleDeeDir::Left:
		AnimationName = "WaddleDeeLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

unsigned int WaddleDee::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void WaddleDee::Movement(float _Delta)
{
	if (Dir == WaddleDeeDir::Left)
	{
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };

		// ������
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = WaddleDeeDir::Right;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
	else if (Dir == WaddleDeeDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };
		MovePos = { Speed * _Delta, 0.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = WaddleDeeDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
}