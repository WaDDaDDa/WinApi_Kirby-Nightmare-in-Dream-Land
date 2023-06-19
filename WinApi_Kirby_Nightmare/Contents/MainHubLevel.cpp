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

	Kirby::SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->OverOn();
	Kirby::GetMainPlayer()->SetPos(StartPlayerPos);

	CreateActor<UIManager>();

	Stage1Portal = CreateActor<Portal>();
	Stage1Portal->SetPos(float4{ 440, 1100 });

	Stage2Portal = CreateActor<Portal>();
	Stage2Portal->SetPos(float4{ 960, 1220 });
}


void MainHubLevel::Update(float _Delta)
{
	CameraFocus();

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("VegetableValley3Level");
		Kirby::GetMainPlayer()->SetGroundTexture("Level3_Debug.bmp");
		Kirby::GetMainPlayer()->SetPos(float4{ 2400,510 });
		//Kirby::GetMainPlayer()->SetPos(Kirby::GetMainPlayer()->GetPrevPos());
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
		float4 PrevPos = Kirby::GetMainPlayer()->GetPos();
		Kirby::GetMainPlayer()->Death();
		Kirby::SetMainPlayer(CreateActor<BurningKirby>());
		Kirby::GetMainPlayer()->SetPos(PrevPos);
		Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
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
				Kirby::GetMainPlayer()->SetGroundTexture("Level1_Debug.bmp");
				// 포탈입장전 현재위치를 저장
				Kirby::GetMainPlayer()->SetPrevPos(Kirby::GetMainPlayer()->GetPos());
				// stage1의 시작위치
				Kirby::GetMainPlayer()->SetPos(Stage1StartPos);
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
				Kirby::GetMainPlayer()->SetGroundTexture("Level2_Debug.bmp");
				// 포탈입장전 현재위치를 저장
				Kirby::GetMainPlayer()->SetPrevPos(Kirby::GetMainPlayer()->GetPos());
				// stage2의 시작위치
				Kirby::GetMainPlayer()->SetPos(Stage2StartPos);
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
	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
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