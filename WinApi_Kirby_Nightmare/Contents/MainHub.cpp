#include "MainHub.h"
#include "MainHubLevel.h"



MainHub::MainHub()
{

}

MainHub::~MainHub()
{

}

// �غ�.
void MainHub::Start()
{
	GameEngineCore::CreateLevel<MainHubLevel>("MainHubLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("MainHubLevel");
}

// �ൿ.
void MainHub::Update()
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