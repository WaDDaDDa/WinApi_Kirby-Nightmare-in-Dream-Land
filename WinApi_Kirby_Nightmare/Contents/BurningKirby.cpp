#include "BurningKirby.h"
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

BurningKirby* BurningKirby::MainPlayer = nullptr;

BurningKirby::BurningKirby()
{

}

BurningKirby::~BurningKirby()
{

}

void BurningKirby::Start()
{
	// 로딩 되어있지 않다면 로드하고, 로딩 되어 있다면 다시 로드하지 않는다.
	// 중복 로드하면 릭이 계속 생긴다.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("BurningKirbyLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BurningKirbyLeft.bmp"), 7, 49);
		}
		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BurningKirbyRight.bmp"), 7, 49);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation 생성
		MainRenderer->CreateAnimation("BurningKirbyLeft_Idle", "BurningKirbyLeft.bmp", 0, 6, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_DownIdle", "BurningKirbyLeft.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_Tackle", "BurningKirbyLeft.bmp", 0, 1, 0.1f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_Walk", "BurningKirbyLeft.bmp", 0, 9, 0.05f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Jump", "BurningKirbyLeft.bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_JumpTurn", "BurningKirbyLeft.bmp", 1, 7, 0.03f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Falling", "BurningKirbyLeft.bmp", 8, 8, 1.0f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_FallingEnd", "BurningKirbyLeft.bmp", 9, 9, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Run", "BurningKirbyLeft.bmp", 0, 7, 0.1f, true);  // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("BurningKirbyLeft_Fly", "BurningKirbyLeft.bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_BreathIn", "BurningKirbyLeft.bmp", 0, 4, 0.05f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("BurningKirbyLeft_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_AttackStart", "BurningKirbyLeft.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Attack", "BurningKirbyLeft.bmp", 3, 4, 0.05f, true);
	}

	{ // RightAnimation 생성
		MainRenderer->CreateAnimation("BurningKirbyRight_Idle", "BurningKirbyRight.bmp", 0, 4, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyRight_DownIdle", "BurningKirbyRight.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyRight_Tackle", "BurningKirbyRight.bmp", 0, 1, 0.1f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("BurningKirbyRight_Walk", "BurningKirbyRight.bmp", 0, 9, 0.05f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Jump", "BurningKirbyRight.bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_JumpTurn", "BurningKirbyRight.bmp", 1, 7, 0.03f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Falling", "BurningKirbyRight.bmp", 8, 8, 1.0f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_FallingEnd", "BurningKirbyRight.bmp", 9, 9, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Run", "BurningKirbyRight.bmp", 0, 7, 0.1f, true); // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("BurningKirbyRight_Fly", "BurningKirbyRight.bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_BreathIn", "BurningKirbyRight.bmp", 0, 4, 0.05f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("BurningKirbyRight_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("BurningKirbyRight_AttackStart", "BurningKirbyRight.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Attack", "BurningKirbyRight.bmp", 3, 4, 0.05f, true);
	}

	{ // 충돌체 설정
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::Rect);
		AttackCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);
	SetPos(float4{ 360,360 });

	// PlayerPos 는 static 멤버 변수 선언후 초기 위치를 선언하고 시작할수있을듯.
	ChangeState(KirbyState::Idle);
}

void BurningKirby::Update(float _Delta)
{
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

			//Actor->Death();
		}
	}

	// 줌 인 아웃 기능
	if (true == GameEngineInput::IsPress('L'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		// GameEngineLevel::CollisionDebugRenderSwitch();
	}


	StateUpdate(_Delta);

	CameraFocus(_Delta);
}

void BurningKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "BurningKirbyRight_";
		break;
	case KirbyDir::Left:
		AnimationName = "BurningKirbyLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}
