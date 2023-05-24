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

		float4 Scale = Text->GetScale();

		Scale.X *= 4.0f;
		Scale.Y *= 4.0f;

		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);

		Render->SetRenderScale(Scale);
	}

}