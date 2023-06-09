#pragma once
#include "GameEngineRenderer.h"
#include <map>
#include <list>

// ���� :
class GameEngineRenderer;
class GameEngineCamera
{
	friend class GameEngineActor;
	friend class GameEngineLevel;
	friend class GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _Value)
	{
		Pos = _Value;
	}

	void AddPos(const float4& _Value)
	{
		Pos += _Value;
	}

protected:

private:
	std::map<int, std::list<GameEngineRenderer*>> Renderers;

	float4 Pos = float4::ZERO;

	void PushRenderer(GameEngineRenderer* _Renderer, int _Order);

	void Render(float _Delta);

	void Release();

	void OverRelease();
};

