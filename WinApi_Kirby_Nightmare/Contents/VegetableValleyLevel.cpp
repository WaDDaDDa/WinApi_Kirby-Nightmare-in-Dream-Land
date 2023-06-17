#include "VegetableValleyLevel.h"
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

VegetableValleyLevel::VegetableValleyLevel()
{

}

VegetableValleyLevel::~VegetableValleyLevel()
{

}

void VegetableValleyLevel::Start()
{
	if (nullptr == GameEngineSound::FindSound("04Vegetable_Valley.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
	}

	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("Level1.Bmp", "Level1_Debug.bmp");

	CreateActor<UIManager>();
	MainPortal = CreateActor<Portal>();
	MainPortal->SetPos(float4{ 3900, 290 });
}


void VegetableValleyLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{

		GameEngineCore::ChangeLevel("MainHubLevel");
		Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
		float4 Ppos = Kirby::GetMainPlayer()->GetPos();
		Kirby::GetMainPlayer()->SetPos(Kirby::GetMainPlayer()->GetPrevPos());
		Kirby::GetMainPlayer()->SetPrevPos(Ppos);
		BGMPlayer.Stop();
		return;

		//GameEngineCore::ChangeLevel("MainHubLevel");
		//Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
		//float4 Ppos = Kirby::GetMainPlayer()->GetPos();
		//Kirby::GetMainPlayer()->SetPos(Kirby::GetMainPlayer()->GetPrevPos());
		//Kirby::GetMainPlayer()->SetPrevPos(Ppos);
		//BGMPlayer.Stop();
		//return;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level1_Debug.bmp");
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
				GameEngineCore::ChangeLevel("VegetableValley2Level");
				Kirby::GetMainPlayer()->SetGroundTexture("Level2_Debug.bmp");
				float4 Ppos = Kirby::GetMainPlayer()->GetPrevPos();
				Kirby::GetMainPlayer()->SetPos(float4 { 300, 370 });
				Kirby::GetMainPlayer()->SetPrevPos(Ppos);
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}
}


void VegetableValleyLevel::Release()
{

}

void VegetableValleyLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Monster::AllMonsterDeath();

	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	Kirby::GetMainPlayer()->SetGroundTexture("Level1_Debug.bmp");
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");

	// ���� ��ġ
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level1_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level1_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}

}

void VegetableValleyLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}