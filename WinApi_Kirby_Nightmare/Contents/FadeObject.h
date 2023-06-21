#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class Fade
{
	FadeOut,
	FadeIn,
};

// Ό³Έν :
class FadeObject : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	void SetFade(bool _Fade)
	{
		FadeDir = _Fade;
	}

	float GetValue()
	{
		return Value;
	}

	void StateUpdate(float _Delta);

	void FadeIn();
	void FadeInUpdate(float _Delta);

	void FadeOut();
	void FadeOutUpdate(float _Delta);

protected:

private:
	float Value = 255.0f;
	bool FadeDir = true;
	GameEngineRenderer* Render;
	Fade FadeValue = Fade::FadeIn;

	void Start() override;
	void Update(float _Time) override;
};

