#pragma once
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <map>
#include <vector>

enum class CameraType
{
	MAIN,
	UI,
};

// 설명 :
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

	CameraType GetCameraType()
	{
		return CameraTypeValue;
	}

	void SetAngle(float _Angle);

	void SetAlpha(unsigned char _Alpha);


protected:
	void Start() override;

private:
	GameEngineCamera* Camera = nullptr;
	GameEngineSprite* Sprite = nullptr;
	// 렌더러는 텍스쳐를 알고있다.
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineWindowTexture* MaskTexture = nullptr;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;
	CameraType CameraTypeValue = CameraType::MAIN;
	std::string Text;

	void TextRender(float _DeltaTime);

	// true이면 셋팅한 크기로 이미지를 출력
	// false이면 이미지 크기그대로 출력
	bool ScaleCheck = false;
	// 이미지 배율
	float ScaleRatio = 1.0f;
	float Angle = 0.0f;
	unsigned char Alpha = 255;

	void Render(float _DeltaTime);

///////////////////////////////////////////////////애니메이션
private:
	class Animation
	{
	public:
		std::string Name = "";
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		std::vector<size_t> Frames;
		std::vector<float> Inters;
		bool Loop = true;
		bool IsEnd = false;
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

	void CreateAnimationToFrame(
		const std::string& _AniamtionName,
		const std::string& _SpriteName,
		const std::vector<size_t>& _Frame,
		float _Inter = 0.1f,
		bool _Loop = true);

	void ChangeAnimation(const std::string& _AniamtionName, int _StartFrame = 0, bool _ForceChange = false);

	void MainCameraSetting();
	void UICameraSetting();

	void Update(float _Delta) override;

	size_t GetCurFrame()
	{
		return CurAnimation->CurFrame;
	}

	bool IsAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	bool IsAnimation(const std::string& _Name)
	{
		return CurAnimation->Name == _Name;
	}
	
private:
	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;

	/////////////////////////////////// Text관련
public:
	void SetText(const std::string& _Text, int _TextScale = 20, const std::string& _Face = "굴림")
	{
		Text = _Text;
		TextScale = _TextScale;
		Face = _Face;
	}

private:
	std::string Face;
	int TextScale;
};

