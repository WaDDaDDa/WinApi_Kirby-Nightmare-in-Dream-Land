#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� :
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

	// �̹����ڵ��� �޾Ƽ� �� �̹����ڵ鿡 �����صд�.
	// �������� �⺻�̹����� ����ϴ� �ڵ��� �״�� �޾Ƽ�.
	// �� �⺻�̹������� ResLoad�� ���� ��ü�ϰ� �̹����� �׸��� ������ �������̴�.
	void ResCreate(HDC  _ImageDC)
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);

	// ���� ���� �̹����� �׷����� �䱸�ϴ� �ڵ��� ��´�.
	HDC GetImageDC()
	{
		return ImageDC;
	}

	float4 GetScale();

	// �⺻��
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& Pos, const float4& Scale);
	// ũ�⸦ ���ڷ� �����ʾƵ� ����Ҽ��ְ� ���� ��.
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& Pos);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale,
					const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 0, 255));

	unsigned int GetColor(unsigned int _DefaultColor, float4 _Pos);

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	// �̹����� ũ�⸦ ��Ÿ��.
	BITMAP Info;

	void ScaleCheck();
};

