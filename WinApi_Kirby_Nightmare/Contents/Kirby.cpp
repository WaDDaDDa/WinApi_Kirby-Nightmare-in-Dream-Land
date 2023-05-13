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
#include "Bullet.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BackGround.h"

Kirby::Kirby()
{

}

Kirby::~Kirby()
{

}


void Kirby::Start()
{
	// �ε� �Ǿ����� �ʴٸ� �ε��ϰ�, �ε� �Ǿ� �ִٸ� �ٽ� �ε����� �ʴ´�.
	// �ߺ� �ε��ϸ� ���� ��� �����.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Kirby.Bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		// ��� ������.
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
	float Speed = 1000.0f;
	float4 PlayerPos = GetPos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	MovePos = float4::ZERO;


	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->Renderer->SetTexture("Kirby.Bmp");
		// ������ ǥ���ϴ� xy�� ũ�Ⱑ 1�̾�� �մϴ�.
		NewBullet->SetDir(float4::RIGHT);
		NewBullet->SetPos(GetPos());
	}
	// �÷��̾� �̵�
	AddPos(MovePos);
	PlayerPos = GetPos();
	// ī�޶����̵�   �÷��̾ �����̸� ī�޶� �̵��Ѵ�.

	if (MovePos != float4::ZERO)
	{
		GetLevel()->GetMainCamera()->AddPos(MovePos);

	}

	// ������ ȭ��â ������ �ѱ���ϸ� ī�޶� �����δ�.
	//if (720 < PlayerPos.iX() - CameraPos.iX() || 0 > PlayerPos.iX() - CameraPos.iX())
	//{
	//	GetLevel()->GetMainCamera()->AddPos({MovePos.X, 0});
	//}

	//if (0 < CameraPos.iY() - PlayerPos.iY() || -480 > CameraPos.iY() - PlayerPos.iY())
	//{
	//	GetLevel()->GetMainCamera()->AddPos({ 0, MovePos.Y });
	//}
	
}

void Kirby::Render()
{
	//SetPos({ 200, 200 });
	//SetScale({ 100, 100 });

	////�׸������� �ڵ��� �ʿ���.
	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Kirby.Bmp");
	////                                             ��µ� ũ��                  �̹��� ��ü�� ũ��
	//BackBuffer->TransCopy(FindTexture, GetPos(), { 50, 50 }, { 0,0 }, FindTexture->GetScale());
}

void Kirby::Release()
{
}