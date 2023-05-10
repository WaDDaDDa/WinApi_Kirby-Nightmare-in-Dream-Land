#include "Kirby.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>


Kirby::Kirby()
{

}

Kirby::~Kirby()
{

}


void Kirby::Start()
{
	// 로딩 되어있지 않다면 로드하고, 로딩 되어 있다면 다시 로드하지 않는다.
	// 중복 로드하면 릭이 계속 생긴다.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Kirby.Bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		// 경로 까지만.
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Kirby.Bmp"));
	}

	GameEngineRenderer* PlayerRender = CreateRenderer("Kirby.Bmp", RenderOrder::Play);
	PlayerRender->SetRenderScale({ 50, 50 });
	PlayerRender->SetTexture("Kirby.Bmp");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 PlayerPos = WinScale.Half() + float4({ -100, 80});

	SetPos(PlayerPos);
}

void Kirby::Update(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (0 != GetAsyncKeyState('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (0 != GetAsyncKeyState('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	// 플레이어 이동
	AddPos(MovePos);
	// 카메라의이동   플레이어가 움직이면 카메라도 이동한다.
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}

void Kirby::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	////그리기위한 핸들이 필요함.
	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Kirby.Bmp");
	////                                             출력될 크기                  이미지 자체의 크기
	//BackBuffer->TransCopy(FindTexture, GetPos(), { 50, 50 }, { 0,0 }, FindTexture->GetScale());
}

void Kirby::Release()
{
}