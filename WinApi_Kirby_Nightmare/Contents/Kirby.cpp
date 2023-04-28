#include "Kirby.h"
#include <GameEnginePlatform/GameEngineWindow.h>

Kirby::Kirby()
{

}

Kirby::~Kirby()
{

}


void Kirby::Start()
{
	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Kirby::Update()
{
	AddPos({ 1.0f, 0.0f });
}

void Kirby::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	// �׸������� �ڵ��� �ʿ���.
	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();

	// 
	Rectangle(WindowDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY()
	);

	// �׷�����?
}

void Kirby::Release()
{
}