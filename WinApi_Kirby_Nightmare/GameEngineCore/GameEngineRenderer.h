#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <map>

// 설명 :
class GameEngineWindowTexture;
class GameEngineActor;
class GameEngineCamera;
class GameEngineSprite;
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

	void SetRenderScaleToTexture();

	bool IsDeath() override;

protected:

private:

	GameEngineSprite* Sprite = nullptr;
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

	void Render(GameEngineCamera* _Camera, float _DeltaTime);

private:
	class Animation
	{
	public:
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		float Inter = 0.1f;
		bool Loop = true;
	};

public:
	Animation* FindAnimation(const std::string& _AniamtionName);

	/// <summary>
	/// 애니메이션 생성함수
	/// </summary>
	/// <param name="_AniamtionName">애니메이션 이름</param>
	/// <param name="_SpriteName">스프라이트 이름</param>
	/// <param name="_Start">시작 프레임</param>
	/// <param name="_End">끝 프레임</param>
	/// <param name="_Inter">애니메이션 시간</param>
	/// <param name="_Loop">애니메이션 반복</param>
	void CreateAnimation(
		const std::string& _AniamtionName,
		const std::string& _SpriteName,
		size_t _Start = -1, size_t _End = -1,
		float _Inter = 0.1f,
		bool _Loop = true);

	void ChangeAnimation(const std::string& _AniamtionName, bool _ForceChange = false);


	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
};

