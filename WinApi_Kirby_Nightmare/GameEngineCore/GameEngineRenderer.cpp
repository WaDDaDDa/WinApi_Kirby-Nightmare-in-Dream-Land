#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include "ResourcesManager.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐를 세팅하려고 했습니다." + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

// 렌더 스케일을 이미지 그대로의 크기로 바꾸고 ScaleCheck를 False로 한다.
void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스쳐가 셋팅되지 않은 렌더러 입니다.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
	// BackBuffer->TransCopy(출력할 이미지, 출력될 엑터의 위치 + 출력될 이미지의 위치 - 카메라의 위치,
	//                          출력될 크기, 출력할 이미지의 시작점, 출력할 이미지의 끝점);

	// 카메라의 위치가 출력에 관여하는것 = 이동에 따른 카메라의 이동을 표현하기 위함.

}

bool GameEngineRenderer::IsDeath()
{
	// 랜더의 주체가되는 객체가 죽었다면 그것또한 렌더에게는 죽음이다.
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}