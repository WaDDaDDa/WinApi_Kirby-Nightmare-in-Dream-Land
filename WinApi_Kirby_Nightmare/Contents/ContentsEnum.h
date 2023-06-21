#pragma once

enum class UpdateOrder
{
	Map,
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	Stage,
	BackEffect,
	Play,
	Effect,
	Effect2,
	PlayUI,
};

enum class CollisionOrder
{
	Map,
	Portal,
	PlayerBody,
	MonsterBody,
	DeathBody,
	VacumAttack,   // 커비의 흡수 공격
	PlayerAttack,  // 별이나 Airatt같은거
	BurningAttack, // 커비의 버닝어택
	SparkAttack,
	MonsterFireAttack, // 몬스터의 화염 공격
};

enum class Abillity
{
	Normal,
	Burning,
	Spark,
};