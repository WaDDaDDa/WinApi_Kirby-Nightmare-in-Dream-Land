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
		MainRenderer->CreateAnimation("BurningKirbyLeft_Tackle", "BurningKirbyLeft.bmp", 80, 84, 0.1f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_Walk", "BurningKirbyLeft.bmp", 96, 105, 0.05f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Jump", "BurningKirbyLeft.bmp", 85, 85, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_JumpTurn", "BurningKirbyLeft.bmp", 87, 93, 0.03f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Falling", "BurningKirbyLeft.bmp", 94, 94, 1.0f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_FallingEnd", "BurningKirbyLeft.bmp", 95, 95, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Run", "BurningKirbyLeft.bmp", 0, 7, 0.1f, true);  // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("BurningKirbyLeft_Fly", "BurningKirbyLeft.bmp", 151, 158, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_BreathIn", "BurningKirbyLeft.bmp", 130, 134, 0.05f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("BurningKirbyLeft_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_AttackStart", "BurningKirbyLeft.bmp", 298, 300, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Attack", "BurningKirbyLeft.bmp", 301, 320, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_BreathOut", "BurningKirbyLeft.bmp", 164, 165, 0.1f, false);
	}

	{ // RightAnimation 생성
		MainRenderer->CreateAnimation("BurningKirbyRight_Idle", "BurningKirbyRight.bmp", 0, 4, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_Idle")->Inters[2] = 0.0f;
		MainRenderer->FindAnimation("BurningKirbyRight_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyRight_DownIdle", "BurningKirbyRight.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyRight_Tackle", "BurningKirbyRight.bmp", 80, 84, 0.1f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("BurningKirbyRight_Walk", "BurningKirbyRight.bmp", 96, 105, 0.05f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Jump", "BurningKirbyRight.bmp", 85, 85, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_JumpTurn", "BurningKirbyRight.bmp", 87, 93, 0.03f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Falling", "BurningKirbyRight.bmp", 94, 94, 1.0f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_FallingEnd", "BurningKirbyRight.bmp", 95, 95, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_Run", "BurningKirbyRight.bmp", 0, 7, 0.1f, true); // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("BurningKirbyRight_Fly", "BurningKirbyRight.bmp", 151, 158, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_BreathIn", "BurningKirbyRight.bmp", 130, 134, 0.05f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("BurningKirbyRight_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("BurningKirbyRight_AttackStart", "BurningKirbyRight.bmp", 298, 300, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_Attack", "BurningKirbyRight.bmp", 301, 320, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_BreathOut", "BurningKirbyRight.bmp", 164, 165, 0.1f, false);
	}

	{ // 충돌체 설정
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		AttackCollision = CreateCollision(CollisionOrder::SpecialAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::Rect);
		AttackCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);
	SetPos(float4{ 360,360 });
	SetAbillity(Abillity::Burning);
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

void BurningKirby::CameraFocus(float _Delta)
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	int CameraRangeX = GetLevel()->GetMainCamera()->GetPos().iX();
	int CameraRangeY = GetLevel()->GetMainCamera()->GetPos().iY();

	int PlayerX = GetPos().iX();
	int PlayerY = GetPos().iY();

	float ImageX = GetGroundTexture()->GetScale().X - 960.0f;
	float ImageY = GetGroundTexture()->GetScale().Y;

	// 카메라가 맵의 왼쪽으로 못나가게.
	if (0 >= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ 0.0f, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// 카메라가 맵의 오른쪽 최대치를 못나가게.
	if (ImageX <= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ ImageX, GetLevel()->GetMainCamera()->GetPos().Y });
	}

	if (0 >= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		//GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, 0.0f });
	}

	// 카메라가 움직이는 X 범위 250 ~ 650 사이에캐릭터를 둔다.
	// 카메라의 속도는 캐릭터의 속도로 한다.
	if (650 < PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({ Speed * _Delta , 0 });
	}
	else if (250 > PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({ -Speed * _Delta , 0 });
	}

	// 카메라가 움직이는 Y범위 캐릭터가 -200 ~ -450 사이에서 움직인다.
	// 캐릭터 이동속도가 카메라 보다 빨라지면 중력을 속도로 한다.
	if (-200 < CameraRangeY - PlayerY)
	{
		if (GetGravityVector().iY() <= -1)
		{
			GetLevel()->GetMainCamera()->AddPos(GetGravityVector() * _Delta);
			return;
		}
		GetLevel()->GetMainCamera()->AddPos(float4::UP);
	}
	else if (-450 > CameraRangeY - PlayerY)
	{
		if (GetGravityVector().iY() >= 1)
		{
			GetLevel()->GetMainCamera()->AddPos(GetGravityVector() * _Delta);
			return;
		}
		GetLevel()->GetMainCamera()->AddPos(float4::DOWN);
	}
}