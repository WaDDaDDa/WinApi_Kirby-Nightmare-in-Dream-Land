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
	Player,
	Effect,
	Effect2,
	PlayUI,
};

enum class CollisionOrder
{
	Map,
	Portal,
	PlayerCore,
	PlayerBody,
	MonsterBody,
	BossMonsterBody,
	DeathBody,
	BossAttack,
	VacumAttack,   // 커비의 흡수 공격
	PlayerAttack,  // 별이나 Airatt같은거
	BurningAttack, // 커비의 버닝어택
	SparkAttack,    //커비의 전기공격
	MonsterFireAttack, // 몬스터의 화염 공격
	MonsterSparkAttack, // 몬스터의 전기 공격
	SwordAttack,
	MonsterSwordAttack,
};

enum class Abillity
{
	Normal,
	Burning,
	Spark,
	Sword,
	Wheel,
};