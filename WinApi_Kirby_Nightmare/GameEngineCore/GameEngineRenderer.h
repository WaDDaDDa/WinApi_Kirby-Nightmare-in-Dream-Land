#pragma once
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <map>
#include <vector>

// ���� :
class GameEngineWindowTexture;
class GameEngineActor;
class GameEngineCamera;
class GameEngineSprite;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineCamera;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetSprite(const std::string& _Name, size_t _Index = 0);

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

	void SetScaleRatio(const float& _Scale)
	{
		ScaleRatio = _Scale;
	}

	void SetRenderScaleToTexture();

	void SetOrder(int _Order) override;

protected:
	void Start() override;

private:
	GameEngineCamera* Camera = nullptr;
	GameEngineSprite* Sprite = nullptr;
	// �������� �ؽ��ĸ� �˰��ִ�.
	GameEngineWindowTexture* Texture = nullptr;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;

	// true�̸� ������ ũ��� �̹����� ���
	// false�̸� �̹��� ũ��״�� ���
	bool ScaleCheck = false;
	// �̹��� ����
	float ScaleRatio = 1.0f;
	void Render(float _DeltaTime);

private:
	class Animation
	{
	public:
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		std::vector<size_t> Frames;
		std::vector<float> Inters;
		bool Loop = true;
	};

public:
	Animation* FindAnimation(const std::string& _AniamtionName);

	/// <summary>
	/// �ִϸ��̼� �����Լ�
	/// </summary>
	/// <param name="_AniamtionName">�ִϸ��̼� �̸�</param>
	/// <param name="_SpriteName">��������Ʈ �̸�</param>
	/// <param name="_Start">���� ������</param>
	/// <param name="_End">�� ������</param>
	/// <param name="_Inter">�ִϸ��̼� �ð�</param>
	/// <param name="_Loop">�ִϸ��̼� �ݺ�</param>
	void CreateAnimation(
		const std::string& _AniamtionName,
		const std::string& _SpriteName,
		size_t _Start = -1, size_t _End = -1,
		float _Inter = 0.1f,
		bool _Loop = true);

	void ChangeAnimation(const std::string& _AniamtionName, bool _ForceChange = false);

	void MainCameraSetting();
	void UICameraSetting();

	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
};

