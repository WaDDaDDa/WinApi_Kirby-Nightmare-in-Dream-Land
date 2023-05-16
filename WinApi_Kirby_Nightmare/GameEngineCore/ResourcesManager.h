#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// ���� : �������� ���������� �˷��ִ� �̱���
// �̱����� ����?
// �̱����� ������������� 1990�� ���α׷��� ������
// ��ټ��� ���α׷��Ӱ� ����� �԰��� �ڵ��� �ϴ°��� �����ϰ� �̸��� ���ΰ��� 
// ������ �����̶�� �ϴµ� ���߿��� �ϳ��� ���ϸ�
// ���� UML�� �Բ� ���°��� ����.
// ���� ���п� �ش�
// ���� ��ü�� �����ϴ� ����� 
// ���� �Ҿ� �����θ� �˰������� �˴ϴ�.
// �� ���α׷����� �� ��ü�� 1���� �־����� ���ڴ�.
class GameEngineSprite;
class GameEngineWindowTexture;
class ResourcesManager
{
public:
	// delete Function
	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	// 3. �������ش�.
	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	// ���ϸ��� �� ã������ �̸��� �ȴ�.
	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	bool IsLoadTexture(const std::string& _Image);

	GameEngineSprite* FindSprite(const std::string& _Name);

	GameEngineSprite* CreateSpriteSheet(const std::string& _TexturePath, int _XCount, int _YCount)
	{
		GameEnginePath Path = _TexturePath;

		return CreateSpriteSheet(Path.GetFileName(), _TexturePath, _XCount, _YCount);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _TexturePath, int _XCount, int _YCount);

	GameEngineSprite* CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path);

protected:

private:
	// 2. ���ο� static �����͵� ���̵� ���� 1���� �д�.
	static ResourcesManager Inst;

	// static ResourcesManager* Inst;

	// 1. �����ڸ� private�ȿ� �ִ´�.
	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineWindowTexture*> AllTexture;

	std::map<std::string, GameEngineSprite*> AllSprite;
};

