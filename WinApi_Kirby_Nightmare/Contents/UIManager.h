#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class UIManager : public GameEngineActor
{
public:
	static UIManager* UI;

public:
	// constrcuter destructer
	UIManager();
	~UIManager();

	// delete Function
	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	GameEngineRenderer* UIRenderer = nullptr;
};

