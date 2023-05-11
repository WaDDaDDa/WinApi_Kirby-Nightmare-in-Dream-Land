#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>

// ���� :
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
	// �������� �ؽ��ĸ� �˰��ִ�.
	GameEngineWindowTexture* Texture = nullptr;
	// ���� �ϰԵ� ���͸� �˰��ִ�.
	GameEngineActor* Master = nullptr;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;

	// true�̸� ������ ũ��� �̹����� ���
	// false�̸� �̹��� ũ��״�� ���
	bool ScaleCheck = false;

	void Render(GameEngineCamera* _Camera);
};

