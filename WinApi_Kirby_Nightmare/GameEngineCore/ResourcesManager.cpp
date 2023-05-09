#include "ResourcesManager.h"
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineBase/GameEngineString.h>

ResourcesManager ResourcesManager::Inst;

// 포인터로 싱글톤을하면 delete 할수있는 장점? 이있는데 그럴거면 뭐하러 싱글톤하냐?
// ResourcesManager* ResourcesManager::Inst = new ResourcesManager();
// ResourcesManager* ResourcesManager::Inst;


bool ResourcesManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{

	for (const std::pair<std::string, GameEngineWindowTexture*>& Pair : AllTexture)
	{
		// GameEngineTexture를 동적바인딩 했기때문에 delete해야함.
		GameEngineWindowTexture* Texture = Pair.second;

		if (nullptr != Texture)
		{
			delete Texture;
			Texture = nullptr;
		}
	}
}


GameEngineWindowTexture* ResourcesManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineWindowTexture*>::iterator FindIter = AllTexture.find(UpperName);

	if (FindIter == AllTexture.end())
	{
		return nullptr;
	}

	return FindIter->second;
}


GameEngineWindowTexture* ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	// 동적 바인딩이라고 합니다.
	GameEngineWindowTexture* LoadTexture = new GameEngineWindowTexture();

	// 경로의 이미지를 그리기위한 권한을 받는다.
	LoadTexture->ResLoad(_Path);

	AllTexture.insert(std::make_pair(UpperName, LoadTexture));

	return LoadTexture;
}