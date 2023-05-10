#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	for (GameEngineRenderer* Renderer : AllRenderer)
	{
		delete Renderer;
		Renderer = nullptr;
	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	GetLevel()->MainCamera->PushRenderer(NewRenderer, _Order);

	NewRenderer->Master = this;
	NewRenderer->SetTexture(_ImageName);
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}