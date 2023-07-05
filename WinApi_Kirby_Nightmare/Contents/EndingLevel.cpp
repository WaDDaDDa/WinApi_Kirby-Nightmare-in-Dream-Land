#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "BGMPlayer.h"
#include "EndingCredit.h"

EndingLevel::EndingLevel()
{

}

EndingLevel::~EndingLevel()
{

}

void EndingLevel::Start()
{
}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	EnD = CreateActor<EndingCredit>();
	BGMPlayer::ChangeBGM("28 Ending.mp3");
}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	EnD->Death();
}

void EndingLevel::Update(float _DeltaTime)
{

}
