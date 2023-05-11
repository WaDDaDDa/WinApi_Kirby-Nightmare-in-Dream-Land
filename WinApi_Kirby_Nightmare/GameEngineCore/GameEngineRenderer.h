#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>

// 설명 :
class GameEngineWindowTexture;
class GameEngineActor;
class GameEngineCamera;
class GameEngineRenderer : public GameEngineObject
{
	friend class GameEngineActor;
	friend class GameEngineCamera;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);

	void SetRenderPos(const float4& _Value)
	{
		RenderPos = _Value;
	}

	void SetRenderScale(const float4& _Value)
	{
		RenderScale = _Value;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Value)
	{
		CopyPos = _Value;
	}

	void SetCopyScale(const float4& _Value)
	{
		CopyScale = _Value;
	}

	void SetRenderScaleToTexture();

	bool IsDeath() override;

protected:

private:
	// 렌더러는 텍스쳐를 알고있다.
	GameEngineWindowTexture* Texture = nullptr;
	// 렌더 하게될 엑터를 알고있다.
	GameEngineActor* Master = nullptr;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;

	// true이면 셋팅한 크기로 이미지를 출력
	// false이면 이미지 크기그대로 출력
	bool ScaleCheck = false;

	void Render(GameEngineCamera* _Camera);
};

