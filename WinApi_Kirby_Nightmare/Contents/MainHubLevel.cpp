#include "MainHubLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "UIManager.h"


// Contents
#include "Kirby.h"
#include "Stage.h"
#include "BackGround.h"
#include "Monster.h"
#include "WaddleDee.h"
#include "BurningKirby.h"
#include "Portal.h"
#include "FadeObject.h"
#include "SparkKirby.h"
#include "SwordKirby.h"

// Kirby* MainHubLevel::LevelPlayer = nullptr;

MainHubLevel::MainHubLevel()
{

}

MainHubLevel::~MainHubLevel()
{

}

void MainHubLevel::Start()
{
	// GlobalVolume 볼륨조절
	GameEngineSound::SetGlobalVolume(0.0f);

	// 사운드 로드
	if (nullptr == GameEngineSound::FindSound("04Vegetable_Valley.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
	}

	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("MainHupBackGround.Bmp");
	CurBackGround->SetScale("MainHupBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("MainHup.Bmp", "MainHupDebug.bmp");

	//Kirby::SetMainPlayer(CreateActor<Kirby>());

	CreateActor<UIManager>();
	
	Stage1Portal = CreateActor<Portal>();
	Stage1Portal->SetPos(Stage1PortalPos);

	Stage2Portal = CreateActor<Portal>();
	Stage2Portal->SetPos(Stage2PortalPos);

	Stage3Portal = CreateActor<Portal>();
	Stage3Portal->SetPos(Stage3PortalPos);

	Stage4Portal = CreateActor<Portal>();
	Stage4Portal->SetPos(Stage4PortalPos);

	Stage5Portal = CreateActor<Portal>();
	Stage5Portal->SetPos(Stage5PortalPos);

	Stage6Portal = CreateActor<Portal>();
	Stage6Portal->SetPos(Stage6PortalPos);

	Stage7Portal = CreateActor<Portal>();
	Stage7Portal->SetPos(Stage7PortalPos);

	Stage8Portal = CreateActor<Portal>();
	Stage8Portal->SetPos(Stage8PortalPos);
}


void MainHubLevel::Update(float _Delta)
{
	//CameraFocus();

	if (true == GameEngineInput::IsDown('P'))
	{
		BGMPlayer.Stop();
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("MainHupDebug.bmp");
		Waddle->SetPos(float4{ 500,360 });
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('K'))
	{
		CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown('Q'))
	{
		Kirby::GetMainPlayer()->ChangeKirby(Abillity::Sword);
	}

	// 포탈 이동
	std::vector<GameEngineCollision*> _Col;

	if (true == Stage1Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("VegetableValleyLevel");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}

	if (true == Stage2Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("VegetableValley2Level");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}


	if (true == Stage3Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("VegetableValley3Level");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}


	if (true == Stage4Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("DesertLevel");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}


	if (true == Stage5Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("DesertLevel2");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}


	if (true == Stage6Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("DesertLevel3");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}


	if (true == Stage7Portal->BodyCollision->Collision(CollisionOrder::PlayerBody
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
				GameEngineCore::ChangeLevel("BossLevel");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}
}


void MainHubLevel::Release()
{

}

void MainHubLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//if (nullptr == Kirby::GetMainPlayer())
	//{
	//	// MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	//	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	//	GetMainCamera()->SetPos(StartPlayerPos + float4{ -WindowScale.hX(), -WindowScale.hY() });
	//}
	//else
	//{
	//	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	//	//GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	//}


	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");

	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();

	Abillity CurAbill = Abillity::Normal;

	if (nullptr != Kirby::GetMainPlayer())
	{
		CurAbill = Kirby::GetMainPlayer()->GetAbillity();
		Kirby::GetMainPlayer()->Death();
	}

	Kirby::GetMainPlayer()->SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->ChangeKirby(CurAbill);
	Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPlayerPos);

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	if (true == GameEngineInput::IsPress('P'))
	{
		Kirby::GetMainPlayer()->SetPos(Stage1PortalPos);
	}
}

void MainHubLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void MainHubLevel::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	int CameraRangeX = GetMainCamera()->GetPos().iX();
	int CameraRangeY = GetMainCamera()->GetPos().iY();

	int PlayerX = Kirby::GetMainPlayer()->GetPos().iX();
	int PlayerY = Kirby::GetMainPlayer()->GetPos().iY();

	float ImageX = Kirby::GetMainPlayer()->GetGroundTexture()->GetScale().X - 960.0f;
	float ImageY = Kirby::GetMainPlayer()->GetGroundTexture()->GetScale().Y - 600.0f;

	if (0.0f >= GetMainCamera()->GetPos().Y)
	{
		GetMainCamera()->SetPos({ GetMainCamera()->GetPos().X, 0.0f });
	}
	return;
}