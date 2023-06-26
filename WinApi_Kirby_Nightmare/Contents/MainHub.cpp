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

// �غ�.
void MainHub::Start()
{
	// GBA�� �ػ� 240x160�� 4������ 960x640�� �� �⺻ �ػ󵵷� �� ����.
	GameEngineWindow::MainWindow.SetPosAndScale({ 0, 0 }, { 960, 600 });
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");
	GameEngineCore::CreateLevel<VegetableValleyLevel>("VegetableValleyLevel");
	GameEngineCore::CreateLevel<VegetableValley2Level>("VegetableValley2Level");
	GameEngineCore::CreateLevel<VegetableValley3Level>("VegetableValley3Level");
	GameEngineCore::CreateLevel<DesertLevel>("DesertLevel");
	GameEngineCore::CreateLevel<DesertLevel2>("DesertLevel2");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("TitleLevel");
}

// �ൿ.
void MainHub::Update(float _Delta)
{
}

// �׷�����.
void MainHub::Render(float _Delta)
{
}

// �����ȴ�.
void MainHub::Release()
{
}