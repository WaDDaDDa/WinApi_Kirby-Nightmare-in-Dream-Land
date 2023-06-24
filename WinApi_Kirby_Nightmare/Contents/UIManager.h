#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class UIType
{
	Icon,
	HP,
};

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

	GameEngineRenderer* GetUIRenderer(UIType _UIType)
	{
		return IconUI;
	}

	void IconChange(Abillity _Kirby);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* IconUI = nullptr;
	float4 IconPos = { 60, 600 };
	float4 IconScale = { 180, 180 };
};

