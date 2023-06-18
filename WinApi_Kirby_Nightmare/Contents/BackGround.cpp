#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineMath.h>
#include "Kirby.h"

#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::BackGround);
	SetPos({ 540, 300 });
}


void BackGround::Update(float _Delta) 
{
	float4 CurCameraPos = GetLevel()->GetMainCamera()->GetPos();
	if (PrevCameraPos != CurCameraPos)
	{
		// 카메라의 움직임을 받아야한다.
		float4 MovePos = CurCameraPos - PrevCameraPos;
		AddPos(MovePos);
		PrevCameraPos = CurCameraPos;
	}
}


void BackGround::Release()
{

}


void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{

		GameEnginePath FilePath;

		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\\\Kirby_Nightmare_in_Dream_Land\\Backgrounds\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	//GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	//float4 Scale = Texture->GetScale();
	//Scale.X *= 4.0f;
	//Scale.Y *= 4.0f;

	MainRenderer->SetTexture(_FileName);
	MainRenderer->SetScaleRatio(1.0f);
	//MainRenderer->SetRenderScale(Scale);
}

void BackGround::SetAnimation(const std::string& _AniamtionName, // 애니메이션 행동 이름
	const std::string& _SpriteName,
	size_t _Start,
	size_t _End,
	float _Inter,
	bool _Loop)
{
	MainRenderer->CreateAnimation(_AniamtionName, _SpriteName, _Start, _End, _Inter, _Loop);

	MainRenderer->ChangeAnimation(_AniamtionName);
	return;
}

void BackGround::SetScale(const std::string& _FileName, float _Value)
{
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();
	Scale.X *= _Value;
	Scale.Y *= _Value;
	MainRenderer->SetRenderScale(Scale);
	return;
}