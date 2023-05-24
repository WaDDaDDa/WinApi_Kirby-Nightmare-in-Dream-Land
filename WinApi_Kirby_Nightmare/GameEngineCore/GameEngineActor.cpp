#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineCollision.h"

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

	for (GameEngineCollision* Collision : AllCollision)
	{
		delete Collision;
		Collision = nullptr;
	}
}

// Mainī�޶� ���� ��µ� ���� ����
GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->Master = this;
	NewRenderer->MainCameraSetting();
	NewRenderer->SetOrder(_Order);

	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

// UI ī�޶� ���� ��µ� ���� ����.
GameEngineRenderer* GameEngineActor::CreateUIRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->Master = this;
	NewRenderer->UICameraSetting();
	NewRenderer->SetOrder(_Order);
	// �̹����� ����ִ� �������� �ƴϸ� ���õ� �̹����� �������ָ� �ȴ�.
	if ("" != _ImageName)
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

// ������ ����.
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
			MsgBoxAssert("nullptr�� ���Ͱ� ������ ����Ʈ�� �� �־����ϴ�.");
			continue;
		}

		delete Renderer; // Renderer�� delete�Ҷ� ������ �߻��Ѵ�.
		Renderer = nullptr;

		// [s] [a] [a]     [a] [e]
		ObjectStartIter = AllRenderer.erase(ObjectStartIter);
	}
}

GameEngineCollision* GameEngineActor::CreateCollision(int _Order/* = 0*/)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();

	NewCollision->Master = this;
	NewCollision->Start();
	NewCollision->SetOrder(_Order);
	AllCollision.push_back(NewCollision);

	return NewCollision;
}