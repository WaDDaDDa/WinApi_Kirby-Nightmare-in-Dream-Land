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
	// ��ü�� create�ɶ� ������ �غ��Ѵ�.
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