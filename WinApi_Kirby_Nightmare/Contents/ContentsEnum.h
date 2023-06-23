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
	DeathBody,
	VacumAttack,   // Ŀ���� ��� ����
	PlayerAttack,  // ���̳� Airatt������
	BurningAttack, // Ŀ���� ���׾���
	SparkAttack,    //Ŀ���� �������
	MonsterFireAttack, // ������ ȭ�� ����
	MonsterSparkAttack, // ������ ���� ����
	SwordAttack,
};

enum class Abillity
{
	Normal,
	Burning,
	Spark,
	Sword,
};