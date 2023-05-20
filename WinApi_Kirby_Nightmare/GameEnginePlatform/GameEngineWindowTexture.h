#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineWindowTexture
{
public:
	// constrcuter destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete Function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);

	// 이미지핸들을 받아서 내 이미지핸들에 저장해둔다.
	// 윈도우의 기본이미지를 출력하는 핸들을 그대로 받아서.
	// 그 기본이미지만을 ResLoad를 통해 교체하고 이미지를 그리는 과정을 가질것이다.
	void ResCreate(HDC  _ImageDC)
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);

	// 내가 가진 이미지를 그려낼때 요구하는 핸들을 얻는다.
	HDC GetImageDC()
	{
		return ImageDC;
	}

	float4 GetScale();

	// 기본형
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& Pos, const float4& Scale);
	// 크기를 인자로 받지않아도 사용할수있게 만든 형.
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& Pos);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale,
					const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 0, 255));

	unsigned int GetColor(unsigned int _DefaultColor, float4 _Pos);

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	// 이미지의 크기를 나타냄.
	BITMAP Info;

	void ScaleCheck();
};

