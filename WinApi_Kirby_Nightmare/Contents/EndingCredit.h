#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class EndingCredit : public GameEngineActor
{
public:
	static EndingCredit* EndingUI;
public:
	EndingCredit();
	~EndingCredit();

	EndingCredit(const EndingCredit& _Other) = delete;
	EndingCredit(EndingCredit&& _Other) noexcept = delete;
	EndingCredit& operator=(const EndingCredit& _Other) = delete;
	EndingCredit& operator=(EndingCredit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* Render = nullptr;
	float4 RenderPos = { 480, 1400 };
};
