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

	Renderer = CreateRenderer(RenderOrder::Stage);

	DebugRenderer = CreateRenderer(RenderOrder::Stage);

	Renderer->On();
	DebugRenderer->Off();
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


void Stage::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;

		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\\\Kirby_Nightmare_in_Dream_Land\\Stages\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);

	float4 Scale = Texture->GetScale();

	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);

	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });
}

// 디버그이미지로 전환.
void Stage::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else 
	{
		Renderer->Off();
		DebugRenderer->On();
	}
}