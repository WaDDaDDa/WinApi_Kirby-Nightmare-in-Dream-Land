#include "Stage.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

Stage::Stage()
{

}

Stage::~Stage()
{

}

void Stage::Start()
{
	SetPos({ 150, 80 });
}


void Stage::Update(float _Delta)
{

}
void Stage::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);
	// BackBuffer->BitCopy(FindTexture, GetPos());

	BackBuffer->BitCopy(FindTexture, GetPos(), { 100, 100 });

}
void Stage::Release()
{

}

void Stage::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Stages\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		float4 Scale = Text->GetScale();

		//Scale.X *= 5.0f;
		//Scale.Y *= 5.0f;

		SetScale(Scale);
	}

}