#include "MainHubLevel.h"
#include "Kirby.h"

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

	CreateActor<Kirby>();
}


void MainHubLevel::Update()
{
}
void MainHubLevel::Render()
{
}
void MainHubLevel::Release()
{
}