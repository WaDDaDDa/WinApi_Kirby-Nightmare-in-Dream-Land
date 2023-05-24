#include "Bullet.h"
#include <GameEngineCore/GameEngineRenderer.h>

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Start()
{
	Renderer = CreateRenderer();
}

void Bullet::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	// 1초뒤 데스
	if (3.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}

}
