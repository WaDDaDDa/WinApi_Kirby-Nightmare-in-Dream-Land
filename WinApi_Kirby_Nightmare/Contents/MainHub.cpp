#include "MainHub.h"
#include "MainHubLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "TitleLevel.h"


MainHub::MainHub()
{

}

MainHub::~MainHub()
{

}

// 준비물.
void MainHub::Start()
{
	// GBA의 해상도 240x160에 3배율한 720x480을 내 기본 해상도로 할 예정.
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 720, 480 });
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");

	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("TitleLevel");
}

// 행동.
void MainHub::Update(float _Delta)
{
}

// 그려지고.
void MainHub::Render()
{
}

// 정리된다.
void MainHub::Release()
{
}