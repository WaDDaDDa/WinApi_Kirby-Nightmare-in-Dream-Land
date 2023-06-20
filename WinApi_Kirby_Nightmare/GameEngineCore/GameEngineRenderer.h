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

	CameraType GetCameraType()
	{
		return CameraTypeValue;
	}

	void SetAngle(float _Angle);

protected:
	void Start() override;

private:
	GameEngineCamera* Camera = nullptr;
	GameEngineSprite* Sprite = nullptr;
	// �������� �ؽ��ĸ� �˰��ִ�.
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineWindowTexture* MaskTexture = nullptr;

	float4 RenderPos;
	float4 RenderScale;

	float4 CopyPos;
	float4 CopyScale;
	CameraType CameraTypeValue = CameraType::MAIN;
	std::string Text;

	void TextRender(float _DeltaTime);

	// true�̸� ������ ũ��� �̹����� ���
	// false�̸� �̹��� ũ��״�� ���
	bool ScaleCheck = false;
	// �̹��� ����
	float ScaleRatio = 1.0f;
	float Angle = 0.0f;

	void Render(float _DeltaTime);

///////////////////////////////////////////////////�ִϸ��̼�
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

	/////////////////////////////////// Text����
public:
	void SetText(const std::string& _Text, int _TextScale = 20, const std::string& _Face = "����")
	{
		Text = _Text;
		TextScale = _TextScale;
		Face = _Face;
	}

private:
	std::string Face;
	int TextScale;
};

