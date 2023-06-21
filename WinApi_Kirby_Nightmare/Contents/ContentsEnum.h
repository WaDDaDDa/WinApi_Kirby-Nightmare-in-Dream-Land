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
	VacumAttack,   // Ŀ���� ��� ����
	PlayerAttack,  // ���̳� Airatt������
	BurningAttack, // Ŀ���� ���׾���
	SparkAttack,    //Ŀ���� �������
	MonsterFireAttack, // ������ ȭ�� ����
	MonsterSparkAttack, // ������ ���� ����
};

enum class Abillity
{
	Normal,
	Burning,
	Spark,
};