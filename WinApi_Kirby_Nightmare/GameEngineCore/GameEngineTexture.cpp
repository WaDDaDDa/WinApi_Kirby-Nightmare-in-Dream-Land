#include "GameEngineTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineTexture::GameEngineTexture()
{
}

GameEngineTexture::~GameEngineTexture()
{
}

// ���ҽ� �ε�
void GameEngineTexture::ResLoad(const std::string& _Path)
{

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� �ε忡 �����߽��ϴ�." + _Path);
		return;
	}

	// �̹����� �ڵ��� ���̰�.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// ���� ������ ���Ӱ� ������ �Ѵ�.
	// Window���� ���� DC
	ImageDC = CreateCompatibleDC(nullptr);
	// �̹����� ���� ������ ����� ����

	// ImageDC ���ѿ�
	// BitMap 2������ ���� ������ �����ض�.
	// ��� �̹� ��������ڸ��� ���ο� 1,1 �̹����� ����Ǿ��ְ�
	// ���� �ε��� �̹����� �� 1,1¥���� �о�� ��ü�ϴ� �۾��� �ϴµ�.
	// �� �Լ��� ���ϰ��� ������ ����Ǿ��ִ� �ָ� �������ִ°�.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);

	BITMAP OldInfo;

	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}