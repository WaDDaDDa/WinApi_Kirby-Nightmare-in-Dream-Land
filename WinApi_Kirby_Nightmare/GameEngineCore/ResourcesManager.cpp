#include "ResourcesManager.h"

ResourcesManager ResourcesManager::Inst;

// �����ͷ� �̱������ϸ� delete �Ҽ��ִ� ����? ���ִµ� �׷��Ÿ� ���Ϸ� �̱����ϳ�?
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

