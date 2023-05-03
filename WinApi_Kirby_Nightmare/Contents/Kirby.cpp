#include "Kirby.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

Kirby::Kirby()
{

}

Kirby::~Kirby()
{

}


void Kirby::Start()
{
	// 로딩 되어있지 않다면 로드하고, 로딩 되어 있다면 다시 로드하지 않는다.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Player_Idle.Bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		ResourcesManager::GetInst().TextureLoad("Player_Idle.Bmp");
	}

	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Kirby::Update(float _Delta)
{
	// 시간 * 이동속도만큼을 계산해서 이동거리를 표현하게 된다.
	AddPos({ 50.0f * _Delta, 0.0f });
}

void Kirby::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	// 그리기위한 핸들이 필요함.
	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();

	// 
	Rectangle(WindowDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY()
	);

	// 그려야죠?
}

void Kirby::Release()
{
}