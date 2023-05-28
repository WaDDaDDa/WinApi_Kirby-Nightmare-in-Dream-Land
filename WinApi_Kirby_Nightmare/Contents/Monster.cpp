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

}

void Monster::Update(float _Delta)
{

}
