#include "DesertLevel2.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineTime.h>
#include "UIManager.h"


// Contents
#include "Kirby.h"
#include "Stage.h"
#include "BackGround.h"
#include "Monster.h"
#include "WaddleDee.h"
#include "BurningKirby.h"
#include "Portal.h"
#include "MainHubLevel.h"
#include "BurningMonster.h"
#include "SparkMonster.h"
#include "FadeObject.h"
#include "SwordMan.h"
#include "BGMPlayer.h"

DesertLevel2::DesertLevel2()
{

}

DesertLevel2::~DesertLevel2()
{

}

void DesertLevel2::Start()
{
	// 백그라운드 사막으로 변경.
	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("DesertBackGround.Bmp");
	CurBackGround->SetScale("DesertBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("DesertLevel2.Bmp", "DesertLevel2_Debug.bmp");

	MainPortal = CreateActor<Portal>();
	MainPortal->Door->Off();
	MainPortal->SubDoor->ChangeAnimation("BlackDoor");
	MainPortal->SubDoor->SetScaleRatio(1.0f);
	MainPortal->SetPos(PortalPos);
}


void DesertLevel2::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
		return;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		SparkMonster* Waddle = CreateActor<SparkMonster>();
		Waddle->SetGroundTexture("DesertLevel2_Debug.bmp");
		Waddle->SetPos(float4{ 500,360 });
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		if (0.0f != GameEngineTime::MainTimer.GetTimeScale(UpdateOrder::Player))
		{
			GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0.0f);
		}
		else
		{
			GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		}

		StagePtr->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('K'))
	{
		CollisionDebugRenderSwitch();
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == MainPortal->BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			if (true == GameEngineInput::IsDown('W'))
			{
				MainPortal->SetCurLevel("DesertLevel3");
				return;
			}
			return;
		}
	}

	if (Kirby::GetMainPlayer()->GetLife() != UIManager::UI->GetCurLife())
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		LevelStart(this);
		return;
	}
}


void DesertLevel2::Release()
{

}

void DesertLevel2::LevelStart(GameEngineLevel* _PrevLevel)
{
	Monster::AllMonsterDeath();

	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();

	BGMPlayer::ChangeBGM("06 Ice Cream Island.mp3");

	Abillity CurAbill = Kirby::GetMainPlayer()->GetAbillity();
	int KirbyLife = Kirby::GetMainPlayer()->GetLife();

	Kirby::GetMainPlayer()->Death();
	Kirby::GetMainPlayer()->SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->ChangeKirby(CurAbill);
	Kirby::GetMainPlayer()->SetGroundTexture("DesertLevel2_Debug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPos);
	Kirby::GetMainPlayer()->SetLife(KirbyLife);

	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	// 몬스터 배치
	{
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("DesertLevel2_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("DesertLevel2_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}
	{
		SparkMonster* Waddle = CreateActor<SparkMonster>();
		Waddle->SetGroundTexture("DesertLevel2_Debug.bmp");
		Waddle->SetPos(float4{ 823,450 });
	}
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel2_Debug.bmp");
		Waddle->SetPos(float4{ 823,450 });
	}
	//{
	//	BurningMonster* Waddle = CreateActor<BurningMonster>();
	//	Waddle->SetGroundTexture("DesertLevel2_Debug.bmp");
	//	Waddle->SetPos(float4{ 1640,1344 });
	//}

}

void DesertLevel2::LevelEnd(GameEngineLevel* _NextLevel)
{

}