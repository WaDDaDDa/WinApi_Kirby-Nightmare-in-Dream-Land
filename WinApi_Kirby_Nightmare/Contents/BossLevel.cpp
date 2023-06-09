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
#include "BossUIManager.h"
#include "BGMPlayer.h"

BossLevel::BossLevel()
{

}

BossLevel::~BossLevel()
{

}

void BossLevel::Start()
{
	// 백그라운드 사막으로 변경.
	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("BossBackGround.Bmp");
	CurBackGround->SetScale("BossBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("BossLevel.Bmp", "BossLevel_Debug.bmp");
}


void BossLevel::Update(float _Delta)
{
	if (Kirby::GetMainPlayer()->GetPos().Y >= 300.0f && Once == false)
	{
		Once = true;
		BUI = CreateActor<BossUIManager>();
	}

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

	if (Kirby::GetMainPlayer()->GetLife() != UIManager::UI->GetCurLife())
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		LevelStart(this);
		return;
	}
	
	if (true == GameEngineInput::IsDown('Q'))
	{
		Kirby::GetMainPlayer()->ChangeKirby(Abillity::Sword);
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
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	if (nullptr != BUI)
	{
		BossMonster::ResetBossHp();
		Once = false;
		BUI->Death();
	}

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();

	BGMPlayer::ChangeBGM("20 Boss Battle.mp3");

	Abillity CurAbill = Kirby::GetMainPlayer()->GetAbillity();
	int KirbyLife = Kirby::GetMainPlayer()->GetLife();

	Kirby::GetMainPlayer()->Death();
	Kirby::GetMainPlayer()->SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->ChangeKirby(CurAbill);
	Kirby::GetMainPlayer()->SetGroundTexture("BossLevel_Debug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPos);
	Kirby::GetMainPlayer()->SetLife(KirbyLife);

	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	WhispyWoods = CreateActor<BossMonster>();
	WhispyWoods->SetPos(float4{ 780.0f , 600.0f});
	WhispyWoods->SetGroundTexture("BossLevel_Debug.bmp");
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}