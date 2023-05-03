#include "ResourcesManager.h"

ResourcesManager ResourcesManager::Inst;

// 포인터로 싱글톤을하면 delete 할수있는 장점? 이있는데 그럴거면 뭐하러 싱글톤하냐?
// ResourcesManager* ResourcesManager::Inst = new ResourcesManager();
// ResourcesManager* ResourcesManager::Inst;


bool ResourcesManager::IsLoadTexture(const std::string& _Image)
{
	return false;
}

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
}

