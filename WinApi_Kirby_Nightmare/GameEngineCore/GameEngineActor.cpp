#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

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
	// 이미지가 비어있는 랜더러가 아니면 세팅될 이미지를 세팅해주면 된다.
	if ("" != _ImageName)
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

// 오류가 있음.
void GameEngineActor::ActorRelease()
{
	std::list<GameEngineRenderer*>::iterator ObjectStartIter = AllRenderer.begin();
	std::list<GameEngineRenderer*>::iterator ObjectEndIter = AllRenderer.end();

	for (; ObjectStartIter != ObjectEndIter; )
	{
		GameEngineRenderer* Renderer = *ObjectStartIter;
		if (false == Renderer->IsDeath())
		{
			++ObjectStartIter;
			continue;
		}


		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
			continue;
		}

		delete Renderer; // Renderer를 delete할때 문제가 발생한다.
		Renderer = nullptr;

		// [s] [a] [a]     [a] [e]
		ObjectStartIter = AllRenderer.erase(ObjectStartIter);

	}
}
