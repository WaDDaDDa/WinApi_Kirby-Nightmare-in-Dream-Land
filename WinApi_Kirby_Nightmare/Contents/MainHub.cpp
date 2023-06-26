#include "MainHub.h"
#include "MainHubLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "TitleLevel.h"
#include "VegetableValleyLevel.h"
#include "VegetableValley2Level.h"
#include "VegetableValley3Level.h"
#include "DesertLevel.h"
#include "DesertLevel2.h"


MainHub::MainHub()
{

}

MainHub::~MainHub()
{

}

// 준비물.
void MainHub::Start()
{
	// GBA의 해상도 240x160에 4배율한 960x640을 내 기본 해상도로 할 예정.
	GameEngineWindow::MainWindow.SetPosAndScale({ 0, 0 }, { 960, 600 });
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");
	GameEngineCore::CreateLevel<VegetableValleyLevel>("VegetableValleyLevel");
	GameEngineCore::CreateLevel<VegetableValley2Level>("VegetableValley2Level");
	GameEngineCore::CreateLevel<VegetableValley3Level>("VegetableValley3Level");
	GameEngineCore::CreateLevel<DesertLevel>("DesertLevel");
	GameEngineCore::CreateLevel<DesertLevel2>("DesertLevel2");

	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("TitleLevel");
}

// 행동.
void MainHub::Update(float _Delta)
{
}

// 그려지고.
void MainHub::Render(float _Delta)
{
}

// 정리된다.
void MainHub::Release()
{
}