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
	VacumAttack,
	PlayerAttack,
	MonsterFireAttack,
	SpecialAttack,
};

enum class Abillity
{
	Normal,
	Burning,
	Spark,
};