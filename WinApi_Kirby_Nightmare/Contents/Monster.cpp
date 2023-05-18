#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include "Kirby.h"

// �̷������� ��� ���͸� �ѹ��� �����Ҽ��ִ�.
std::list<Monster*> Monster::AllMonster;

Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{

}

// ���͸� ���� ���̴� ����� ����Ҽ��ְ� �ȴ�.
void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
	}

	AllMonster.clear();
}


void Monster::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderScale({ 150, 150 });
		Ptr->SetTexture("HPBar.bmp");
	}
}

void Monster::Update(float _Delta)
{
	float4 Dir = Kirby::GetMainPlayer()->GetPos() - GetPos();
	Dir.Normalize();

	AddPos(Dir * _Delta * 100.0f);
}
