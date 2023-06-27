#include "SparkKirby.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BackGround.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineCollision.h>


SparkKirby::SparkKirby()
{

}

SparkKirby::~SparkKirby()
{

}

void SparkKirby::Start()
{
	// 로딩 되어있지 않다면 로드하고, 로딩 되어 있다면 다시 로드하지 않는다.
	// 중복 로드하면 릭이 계속 생긴다.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("SparkKirbyLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkKirbyLeft.bmp"), 8, 30);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkKirbyLeft_Attack.bmp"), 7, 1);
		}
		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkKirbyRight.bmp"), 8, 30);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkKirbyRight_Attack.bmp"), 7, 1);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Player);
	AttRenderer = CreateRenderer(RenderOrder::BackEffect);

	{ // LeftAnimation 생성
		MainRenderer->CreateAnimation("SparkKirbyLeft_Idle", "SparkKirbyLeft.bmp", 0, 6, 0.2f, true);
		MainRenderer->FindAnimation("SparkKirbyLeft_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("SparkKirbyLeft_DownIdle", "SparkKirbyLeft.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("SparkKirbyLeft_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("SparkKirbyLeft_Tackle", "SparkKirbyLeft.bmp", 80, 84, 0.1f, true);
		MainRenderer->FindAnimation("SparkKirbyLeft_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("SparkKirbyLeft_Walk", "SparkKirbyLeft.bmp", 96, 105, 0.05f, true);
		MainRenderer->CreateAnimation("SparkKirbyLeft_Jump", "SparkKirbyLeft.bmp", 85, 85, 0.1f, false);
		MainRenderer->CreateAnimation("SparkKirbyLeft_JumpTurn", "SparkKirbyLeft.bmp", 87, 93, 0.03f, true);
		MainRenderer->CreateAnimation("SparkKirbyLeft_Falling", "SparkKirbyLeft.bmp", 94, 94, 1.0f, false);
		MainRenderer->CreateAnimation("SparkKirbyLeft_FallingEnd", "SparkKirbyLeft.bmp", 95, 95, 0.1f, false);
		MainRenderer->CreateAnimation("SparkKirbyLeft_Run", "SparkKirbyLeft.bmp", 0, 7, 0.1f, true);  // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("SparkKirbyLeft_Fly", "SparkKirbyLeft.bmp", 151, 158, 0.1f, true);
		MainRenderer->CreateAnimation("SparkKirbyLeft_BreathIn", "SparkKirbyLeft.bmp", 130, 134, 0.05f, true);
		MainRenderer->FindAnimation("SparkKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("SparkKirbyLeft_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("SparkKirbyLeft_AttackStart", "SparkKirbyLeft_Attack.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkKirbyLeft_Attack", "SparkKirbyLeft_Attack.bmp", 4, 6, 0.1f, true);
		MainRenderer->CreateAnimation("SparkKirbyLeft_BreathOut", "SparkKirbyLeft.bmp", 164, 165, 0.1f, false);
	}

	{ // RightAnimation 생성
		MainRenderer->CreateAnimation("SparkKirbyRight_Idle", "SparkKirbyRight.bmp", 0, 4, 0.2f, true);
		//MainRenderer->FindAnimation("SparkKirbyRight_Idle")->Inters[2] = 0.0f;
		//MainRenderer->FindAnimation("SparkKirbyRight_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("SparkKirbyRight_DownIdle", "SparkKirbyRight.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("SparkKirbyRight_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("SparkKirbyRight_Tackle", "SparkKirbyRight.bmp", 80, 84, 0.1f, true);
		MainRenderer->FindAnimation("SparkKirbyRight_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("SparkKirbyRight_Walk", "SparkKirbyRight.bmp", 96, 105, 0.05f, true);
		MainRenderer->CreateAnimation("SparkKirbyRight_Jump", "SparkKirbyRight.bmp", 85, 85, 0.1f, false);
		MainRenderer->CreateAnimation("SparkKirbyRight_JumpTurn", "SparkKirbyRight.bmp", 87, 93, 0.03f, true);
		MainRenderer->CreateAnimation("SparkKirbyRight_Falling", "SparkKirbyRight.bmp", 94, 94, 1.0f, false);
		MainRenderer->CreateAnimation("SparkKirbyRight_FallingEnd", "SparkKirbyRight.bmp", 95, 95, 0.1f, false);
		MainRenderer->CreateAnimation("SparkKirbyRight_Run", "SparkKirbyRight.bmp", 0, 7, 0.1f, true); // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("SparkKirbyRight_Fly", "SparkKirbyRight.bmp", 151, 158, 0.1f, true);
		MainRenderer->CreateAnimation("SparkKirbyRight_BreathIn", "SparkKirbyRight.bmp", 130, 134, 0.05f, true);
		MainRenderer->FindAnimation("SparkKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("SparkKirbyRight_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("SparkKirbyRight_AttackStart", "SparkKirbyRight_Attack.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkKirbyRight_Attack", "SparkKirbyRight_Attack.bmp", 4, 6, 0.1f, true);
		MainRenderer->CreateAnimation("SparkKirbyRight_BreathOut", "SparkKirbyRight.bmp", 164, 165, 0.1f, false);
	}

	{ // 충돌체 설정
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);

		AttackCollision = CreateCollision(CollisionOrder::SparkAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::CirCle);
		AttackCollision->Off();

		TackleCollision = CreateCollision(CollisionOrder::PlayerAttack);
		TackleCollision->SetCollisionScale(TackleCollisionScale);
		TackleCollision->SetCollisionPos(TackleCollisionPos);
		TackleCollision->SetCollisionType(CollisionType::CirCle);
		TackleCollision->Off();
	}
	AttRenderer ->SetTexture("Blank.bmp");
	AttRenderer->CreateAnimation("SparkEffect", "SparkEffect.bmp", 0, 3, 0.1f, true);
	AttRenderer->ChangeAnimation("SparkEffect");
	AttRenderer->SetRenderPos(AttackCollisionPos);
	AttRenderer->SetScaleRatio(4.0f);
	AttRenderer->Off();

	MainRenderer->SetScaleRatio(4.0f);
	MainRenderer->SetTexture("Blank.bmp");
	SetOrder(UpdateOrder::Player);
	SetAbillity(Abillity::Spark);
	// PlayerPos 는 static 멤버 변수 선언후 초기 위치를 선언하고 시작할수있을듯.
	ChangeState(KirbyState::Idle);
}

void SparkKirby::LevelStart()
{
	Kirby::GetMainPlayer()->SetMainPlayer(this);
}

void SparkKirby::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	// 충돌함수 사용방법.
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

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::MonsterFireAttack
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::MonsterSparkAttack
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	StateUpdate(_Delta);
	CameraFocus(_Delta);
}

void SparkKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "SparkKirbyRight_";
		break;
	case KirbyDir::Left:
		AnimationName = "SparkKirbyLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}
