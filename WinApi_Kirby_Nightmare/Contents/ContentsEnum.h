#pragma once

enum class UpdateOrder
{
	Player,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	Stage,
	Play,
	Effect,
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
	SpecialAttack,
};

enum class Abillity
{
	Normal,
	Burning,
};