#include "Portal.h"
#include <GameEngineCore/GameEngineCollision.h>

Portal::Portal()
{

}

Portal::~Portal()
{

}

void Portal::Start()
{
	BodyCollision = CreateCollision(CollisionOrder::Portal);
	BodyCollision->SetCollisionScale(BodyCollisionScale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Portal::Update(float _Delta)
{

}
