#include "Stage.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#pragma comment(lib, "msimg32.lib")

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Start()
{
	SetPos({ 640, 360 });
}


void Stage::Update(float _Delta) {
}
void Stage::Render()
{
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);

	if (nullptr == FindTexture)
	{
		return;
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	float4 Scale = FindTexture->GetScale();

	// 720

	Scale *= 2.0f;

	//                BackBuffer�� �׸����� ��ġ     ũ��    
	// BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());                                              
	//                             ī���Ϸ��� �̹�����       ������ġ ũ��
	// BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());                                              
	BackBuffer->TransCopy(FindTexture, GetPos().Half(), Scale, {0,0}, FindTexture->GetScale());

}

void Stage::Release()
{

}


void Stage::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		// ���
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\Bin\x64\Debug
		// 
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\ContentsResources\Texture\Player
		GameEnginePath FilePath;
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi\GameEngineApp
		FilePath.GetCurrentPath();
		// ������ġ D:\Project\AR47\Winapi\AR47WinApi

		// ContentsResources

		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\\\Kirby_Nightmare_in_Dream_Land\\Stages\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		// 208

		float4 Scale = Text->GetScale();

		Scale.X *= 5.0f;
		Scale.Y *= 5.0f;

		// SetScale(Scale * 5.0f);

		SetScale(Scale);
	}

}