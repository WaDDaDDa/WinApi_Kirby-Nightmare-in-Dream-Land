#include "Stage.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

#pragma comment(lib, "msimg32.lib")

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Start()
{
	SetPos({ 1200, 340 });
}


void Stage::Update(float _Delta) {
}
void Stage::Render()
{
	//GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);

	//if (nullptr == FindTexture)
	//{
	//	return;
	//}

	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	//float4 Scale = FindTexture->GetScale();

	//// 720

	//Scale *= 2.0f;

	////                BackBuffer에 그리려는 위치     크기    
	//// BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());                                              
	////                             카피하려는 이미지의       시작위치 크기
	//// BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());                                              
	//BackBuffer->TransCopy(FindTexture, GetPos().Half(), Scale, {0,0}, FindTexture->GetScale());

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

		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\\\Kirby_Nightmare_in_Dream_Land\\Stages\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		float4 Scale = Text->GetScale();

		Scale.X *= 2.4f;
		Scale.Y *= 2.4f;

		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);

		Render->SetRenderScale(Scale);

		SetPos({ Scale.hX(), Scale.hY() });
	}

}