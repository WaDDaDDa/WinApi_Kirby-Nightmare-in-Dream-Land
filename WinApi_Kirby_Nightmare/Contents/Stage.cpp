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
	Renderer = CreateRenderer(RenderOrder::Stage);

	DebugRenderer = CreateRenderer(RenderOrder::Stage);

	Renderer->On();
	DebugRenderer->Off();
}


void Stage::Update(float _Delta)
{

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