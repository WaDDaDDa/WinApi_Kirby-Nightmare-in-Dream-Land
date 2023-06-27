#include "BossLevel.h"
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
#include "BossMonster.h"

BossLevel::BossLevel()
{

}

BossLevel::~BossLevel()
{

}

void BossLevel::Start()
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
	CurBackGround->Init("BossBackGround.Bmp");
	CurBackGround->SetScale("BossBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("BossLevel.Bmp", "BossLevel_Debug.bmp");

}


void BossLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('K'))
	{
		CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Wad = CreateActor<WaddleDee>();
		Wad->SetGroundTexture("BossLevel_Debug.bmp");
		Wad->SetPos(float4{ 500.0f, 500.0f});
	}

}


void BossLevel::Release()
{

}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
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

	Abillity CurAbillity = Kirby::GetMainPlayer()->GetAbillity();
	Kirby::GetMainPlayer()->Death();
	Kirby::SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->ChangeKirby(CurAbillity);
	Kirby::GetMainPlayer()->SetGroundTexture("BossLevel_Debug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPos);
	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	WhispyWoods = CreateActor<BossMonster>();
	WhispyWoods->SetPos(float4{ 780.0f , 600.0f});
	WhispyWoods->SetGroundTexture("BossLevel_Debug.bmp");
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}