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

int GravityActor::GetGroundColor(unsigned int _DefaultColor /*= RGB(255, 255, 255)*/, float4 _Pos /*= float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("����׿� �̹����� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void GravityActor::GroundCheck(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	// �÷��̾� ��ġ�� ����̸� �߷��ۿ�.
	if (RGB(255, 255, 255) == Color && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255))
	{
		Gravity(_Delta);
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
		unsigned int CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
		unsigned int CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);

		// �÷��̾� ��ġ�� ����� �ƴ϶�� �÷��̾� ��ġ�� ��ĭ �ø���.
		while (CheckColor != RGB(255, 255, 255) || CheckLeftColor != RGB(255, 255, 255) || CheckRightColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
			CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);
			AddPos(float4::UP);
		}
		GravityReset();
	}
}
