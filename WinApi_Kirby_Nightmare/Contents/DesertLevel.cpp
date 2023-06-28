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

DesertLevel::DesertLevel()
{

}

DesertLevel::~DesertLevel()
{

}

void DesertLevel::Start()
{
	if (nullptr == GameEngineSound::FindSound("04Vegetable_Valley.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		// BGM �ε� �縷���� ����.
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
	}
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
		BGMPlayer.Stop();
		return;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		SparkMonster* Waddle = CreateActor<SparkMonster>();
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
				BGMPlayer.Stop();
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

	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");

	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();

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
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("DesertLevel1_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}

}

void DesertLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}