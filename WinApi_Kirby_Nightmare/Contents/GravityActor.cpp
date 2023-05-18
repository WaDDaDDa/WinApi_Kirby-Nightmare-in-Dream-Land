#include "GravityActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>



GravityActor::GravityActor()
{

}

GravityActor::~GravityActor()
{

}

void GravityActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}
	GravityVector += float4::DOWN * GravityPower * _Delta;

	AddPos(GravityVector);
}




void GravityActor::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}

}