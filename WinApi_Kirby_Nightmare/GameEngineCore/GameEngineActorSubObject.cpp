#include "GameEngineActorSubObject.h"
#include "GameEngineActor.h"

GameEngineActorSubObject::GameEngineActorSubObject()
{
}

GameEngineActorSubObject::~GameEngineActorSubObject()
{
}


bool GameEngineActorSubObject::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}

bool GameEngineActorSubObject::IsUpdate()
{
	return true == GameEngineObject::IsUpdate() && Master->IsUpdate();
}