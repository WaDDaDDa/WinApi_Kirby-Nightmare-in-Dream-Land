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
	PlayUI,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
	VacumAttack,
	PlayerAttack,
	SpecialAttack,
};

enum class Abillity
{
	Normal,
	Burning,
};