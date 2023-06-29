#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class BossUIManager : public GameEngineActor
{
public:
	static BossUIManager* BossUI;
public:
    BossUIManager();
    ~BossUIManager();

    BossUIManager(const BossUIManager& _Other) = delete;
    BossUIManager(BossUIManager&& _Other) noexcept = delete;
    BossUIManager& operator=(const BossUIManager& _Other) = delete;
    BossUIManager& operator=(BossUIManager&& _Other) noexcept = delete;

	void BossHpCheck();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* BossHpBar = nullptr;
	float4 BossHpPos = { 780, 500 };
	int CurBossHP = 100;
};
