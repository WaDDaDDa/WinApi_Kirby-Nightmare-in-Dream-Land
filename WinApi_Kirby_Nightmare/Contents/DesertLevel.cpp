#include "DesertLevel.h"
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

DesertLevel::DesertLevel()
{

}

DesertLevel::~DesertLevel()
{

}

void DesertLevel::Start()
{
	// ��׶��� �縷���� ����.
	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("DesertBackGround.Bmp");
	CurBackGround->SetScale("DesertBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("DesertLevel1.Bmp", "DesertLevel1_Debug.bmp");

	MainPortal = CreateActor<Portal>();
	MainPortal->Door->Off();
	MainPortal->SetPos(PortalPos);
}


void DesertLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
		return;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
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
		, CollisionType::Rect // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			if (true == GameEngineInput::IsDown('W'))
			{
				MainPortal->SetCurLevel("DesertLevel2");
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


void DesertLevel::Release()
{

}

void DesertLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Monster::AllMonsterDeath();

	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
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
	Kirby::GetMainPlayer()->SetGroundTexture("DesertLevel1_Debug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPos);
	Kirby::GetMainPlayer()->SetLife(KirbyLife);

	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	// ���� ��ġ
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 1450,350 });
		Waddle->Dir = SwordManDir::Left;
	}
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 1023,320 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}

	{
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 3000,570 });
	}
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 3026,448 });
		Waddle->Dir = SwordManDir::Left;
	}
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 3200,320 });
		Waddle->Dir = SwordManDir::Left;
	}
	{
		SwordMan* Waddle = CreateActor<SwordMan>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 3450,192 });
		Waddle->Dir = SwordManDir::Left;
	}
}

void DesertLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}