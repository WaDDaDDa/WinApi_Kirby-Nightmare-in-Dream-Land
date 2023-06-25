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
	float4 IconPos = { 60, 570 };

	GameEngineRenderer* IconName = nullptr;
	float4 IconNamePos = { 60, 585 };

	GameEngineRenderer* LifeIcon = nullptr;
	float4 LifeIconPos = { 250, 560 };

	GameEngineRenderer* LifeNum0 = nullptr;
	float4 LifeNum0Pos = { 330, 560 };

	GameEngineRenderer* LifeNum = nullptr;
	float4 LifeNumPos = { 360, 560 };

	GameEngineRenderer* HpBar1 = nullptr;
	GameEngineRenderer* HpBar2 = nullptr;
	GameEngineRenderer* HpBar3 = nullptr;
	GameEngineRenderer* HpBar4 = nullptr;
	GameEngineRenderer* HpBar5 = nullptr;
	GameEngineRenderer* HpBar6 = nullptr;
	float4 HpBarPos = { 430, 560 };
	float4 HpBarInter = { 32, 0 };

	GameEngineRenderer* ScoreNum0 = nullptr;
	GameEngineRenderer* ScoreNum1 = nullptr;
	GameEngineRenderer* ScoreNum2 = nullptr;
	GameEngineRenderer* ScoreNum3 = nullptr;
	GameEngineRenderer* ScoreNum4 = nullptr;
	GameEngineRenderer* ScoreNum5 = nullptr;
	GameEngineRenderer* ScoreNum6 = nullptr;
	GameEngineRenderer* ScoreNum7 = nullptr;
	GameEngineRenderer* ScoreNum8 = nullptr;
	GameEngineRenderer* ScoreNum9 = nullptr;
	float4 ScoreNumPos = { 720, 560 };
	float4 ScoreNumInter = { 30, 0 };

};

