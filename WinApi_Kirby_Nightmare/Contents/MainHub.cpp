#include "MainHub.h"
#include "MainHubLevel.h"



MainHub::MainHub()
{

}

MainHub::~MainHub()
{

}

// 준비물.
void MainHub::Start()
{
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");

	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("MainHubLevel");
}

// 행동.
void MainHub::Update()
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