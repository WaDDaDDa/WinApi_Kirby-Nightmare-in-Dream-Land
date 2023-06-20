#include "GameEngineSprite.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include "ResourcesManager.h"

GameEngineSprite::GameEngineSprite()
{
}

GameEngineSprite::~GameEngineSprite()
{
}

// 텍스쳐를 X,Y 등분해서 사용할수있게 하는 스프라이트를 만든다
void GameEngineSprite::CreateSpriteSheet(GameEngineWindowTexture* _Texture, int _XCount, int _YCount)
{
	float4 TextureScale = _Texture->GetScale();

	AllSprite.resize(_XCount * _YCount);

	float4 StartPos = { float4::ZERO };
	float4 ImageSize = { TextureScale.X / _XCount, TextureScale.Y / _YCount };


	for (size_t y = 0; y < _YCount; y++)
	{
		for (size_t x = 0; x < _XCount; x++)
		{
			size_t Index = (y * _XCount) + x;

			// 1차원 배열에 순서대로 자른 이미지를 벡터에 넣어주게 된다.
			AllSprite[Index].BaseTexture = _Texture;
			AllSprite[Index].RenderPos.X = StartPos.X;
			AllSprite[Index].RenderPos.Y = StartPos.Y;
			// 자른 이미지의 스프라이트 상에서의 시작점과 끝점을 알아야 출력이 가능할것이다
			AllSprite[Index].RenderScale.X = ImageSize.X;
			AllSprite[Index].RenderScale.Y = ImageSize.Y;

			StartPos.X += ImageSize.X;
		}

		StartPos.X = 0;
		StartPos.Y += ImageSize.Y;
	}
}

// 폴더내의 이미지들을 하나의 스프라이트로 만들어준다.
void GameEngineSprite::CreateSpriteFolder(const std::string& _Path)
{
	GameEngineDirectory Dir = _Path;

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".Bmp" });

	AllSprite.resize(Files.size());

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(Files[i].GetStringPath());
		AllSprite[i].BaseTexture = Texture;
		AllSprite[i].RenderPos = float4::ZERO;
		AllSprite[i].RenderScale = Texture->GetScale();
	}
}

const GameEngineSprite::Sprite& GameEngineSprite::GetSprite(size_t _Index)
{
	static GameEngineSprite::Sprite ReturnValue;

	if (0 > _Index)
	{
		MsgBoxAssert("0보다 작은 스프라이트 인덱스 입니다.");
		return ReturnValue;
	}

	if (AllSprite.size() <= _Index)
	{
		MsgBoxAssert("스프라이트 인덱스 범위를 오버했습니다.");
		return ReturnValue;
	}

	return AllSprite[_Index];
}


void GameEngineSprite::SetMaskTexture(const std::string& _MaskName)
{
	GameEngineWindowTexture* MaskTexture = ResourcesManager::GetInst().FindTexture(_MaskName);

	if (nullptr == MaskTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 마스크로 사용하려고 했습니다.");
	}

	for (size_t i = 0; i < AllSprite.size(); i++)
	{
		AllSprite[i].MaskTexture = MaskTexture;
	}
}