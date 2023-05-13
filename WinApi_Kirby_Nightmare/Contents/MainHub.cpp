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
	// GBA�� �ػ� 240x160�� 3������ 720x480�� �� �⺻ �ػ󵵷� �� ����.
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 720, 480 });
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("TitleLevel");
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