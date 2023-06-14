#include "MainHub.h"
#include "MainHubLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "TitleLevel.h"
#include "VegetableValleyLevel.h"


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

	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("VegetableValleyLevel");
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