#pragma once
#include "GameEngineObject.h"

// 설명 : 랜더러와 콜리전이 오브젝트를 상속받기전 거치는 중간 단계 역할.
class GameEngineActor;
class GameEngineActorSubObject : public GameEngineObject
{
	friend class GameEngineLevel;
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineActorSubObject();
	~GameEngineActorSubObject();

	// delete Function
	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;

	bool IsDeath() override;
	bool IsUpdate() override;

	GameEngineActor* GetActor()
	{
		return Master;
	}

protected:

private:
	GameEngineActor* Master = nullptr;
};

