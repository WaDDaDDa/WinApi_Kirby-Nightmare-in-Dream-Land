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
		MsgBoxAssert("�������� �ʴ� �ؽ��ĸ� �����Ϸ��� �߽��ϴ�." + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

// ���� �������� �̹��� �״���� ũ��� �ٲٰ� ScaleCheck�� False�� �Ѵ�.
void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ��İ� ���õ��� ���� ������ �Դϴ�.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
	// BackBuffer->TransCopy(����� �̹���, ��µ� ������ ��ġ + ��µ� �̹����� ��ġ - ī�޶��� ��ġ,
	//                          ��µ� ũ��, ����� �̹����� ������, ����� �̹����� ����);

	// ī�޶��� ��ġ�� ��¿� �����ϴ°� = �̵��� ���� ī�޶��� �̵��� ǥ���ϱ� ����.

}

bool GameEngineRenderer::IsDeath()
{
	// ������ ��ü���Ǵ� ��ü�� �׾��ٸ� �װͶ��� �������Դ� �����̴�.
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}