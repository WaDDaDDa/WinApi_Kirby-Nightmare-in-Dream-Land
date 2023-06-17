#include "VegetableValley2Level.h"
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
#include "MainHubLevel.h"

VegetableValley2Level::VegetableValley2Level()
{

}

VegetableValley2Level::~VegetableValley2Level()
{

}

void VegetableValley2Level::Start()
{
	if (nullptr == GameEngineSound::FindSound("04Vegetable_Valley.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
	}

	BackGround* CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("Level2.Bmp", "Level2_Debug.bmp");

	CreateActor<UIManager>();
	MainPortal = CreateActor<Portal>();
	MainPortal->SetPos(float4{ 3900, 290 });

	// ���� ��ġ
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}

}


void VegetableValley2Level::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
		BGMPlayer.Stop();

	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 500,360 });
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
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
				GameEngineCore::ChangeLevel("MainHubLevel");
				Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
				Kirby::GetMainPlayer()->SetPos(Kirby::GetMainPlayer()->GetPrevPos());
				Kirby::GetMainPlayer()->SetPrevPos(Kirby::GetMainPlayer()->GetPos());
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}
}


void VegetableValley2Level::Release()
{

}

void VegetableValley2Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	Kirby::GetMainPlayer()->SetGroundTexture("Level2_Debug.bmp");
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
}

void VegetableValley2Level::LevelEnd(GameEngineLevel* _NextLevel)
{

}