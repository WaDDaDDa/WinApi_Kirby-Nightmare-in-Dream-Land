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

// �غ�.
void MainHub::Start()
{
	// GBA�� �ػ� 240x160�� 4������ 960x640�� �� �⺻ �ػ󵵷� �� ����.
	GameEngineWindow::MainWindow.SetPosAndScale({ 0, 0 }, { 960, 600 });
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("MainHubLevel");
}

// �ൿ.
void MainHub::Update(float _Delta)
{
}

// �׷�����.
void MainHub::Render()
{
}

// �����ȴ�.
void MainHub::Release()
{
}