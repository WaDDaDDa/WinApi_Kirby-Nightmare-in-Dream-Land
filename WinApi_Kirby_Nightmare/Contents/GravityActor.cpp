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
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}
}

int GravityActor::GetGroundColor(unsigned int _DefaultColor /*= RGB(255, 255, 255)*/, float4 _Pos /*= float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("디버그용 이미지가 존재하지 않습니다.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void GravityActor::GroundCheck(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int LeftColor = GetGroundColor(RGB(255, 255, 255), LeftCheck);
	unsigned int RightColor = GetGroundColor(RGB(255, 255, 255), RightCheck);

	// 플레이어 위치가 흰색이면 중력작용.
	if (RGB(255, 255, 255) == Color && LeftColor == RGB(255, 255, 255) && RightColor == RGB(255, 255, 255))
	{
		Gravity(_Delta);
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
		unsigned int CheckLeftColor = GetGroundColor(RGB(255, 255, 255), float4::UP + LeftCheck);
		unsigned int CheckRightColor = GetGroundColor(RGB(255, 255, 255), float4::UP + RightCheck);

		// 플레이어 위치가 흰색이 아니라면 플레이어 위치를 한칸 올린다.
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
