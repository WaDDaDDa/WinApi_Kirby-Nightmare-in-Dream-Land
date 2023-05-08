#include "MainHubLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

// Contents
#include "Kirby.h"
#include "Stage.h"

MainHubLevel::MainHubLevel()
{

}

MainHubLevel::~MainHubLevel()
{

}

void MainHubLevel::Start()
{
	// �÷��� ������ ���������.
	// �� �������� ���� �־����?
	// �÷��̾� �����
	// �ʸ����
	// ���� �����
	// ����

	// �ڱ� ���Ǵ�� ����ڴٴ� ���̰� xxxxx
	// Player* NewPlayer = new Player();
	// ��ü�� create�ɶ� ������ �غ��Ѵ�.
	Stage* CurStage = CreateActor<Stage>();
	CurStage->Init("StageTest.Bmp");

	CreateActor<Kirby>();
	CreateActor<Kirby>();
	CreateActor<Kirby>();
}


void MainHubLevel::Update(float _Delta)
{
}
void MainHubLevel::Render()
{
}
void MainHubLevel::Release()
{
}