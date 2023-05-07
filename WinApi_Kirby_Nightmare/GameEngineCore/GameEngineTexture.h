#pragma once
#include <string>
#include <Windows.h>

// 설명 :
class GameEngineTexture
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);

	// 이미지를 그려낼때 요구하는 핸들을 얻는다.
	HDC GetImageDC()
	{
		return ImageDC;
	}

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	BITMAP Info;

	void ScaleCheck();
};

