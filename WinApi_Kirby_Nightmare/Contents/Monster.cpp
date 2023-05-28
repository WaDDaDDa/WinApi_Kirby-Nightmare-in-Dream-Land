#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include "Kirby.h"

// 이런식으로 모든 몬스터를 한번에 관리할수있다.
std::list<Monster*> Monster::AllMonster;

Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{

}

// 몬스터를 전부 죽이는 기능을 사용할수있게 된다.
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
