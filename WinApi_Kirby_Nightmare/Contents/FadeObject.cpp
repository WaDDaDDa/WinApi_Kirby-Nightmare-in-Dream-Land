#include "FadeObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

FadeObject::FadeObject()
{
}

FadeObject::~FadeObject()
{
}

void FadeObject::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("FADE.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");

		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("FADE.bmp"));
	}

	Render = CreateUIRenderer(200);
	Render->SetTexture("FADE.bmp");
	Render->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
	Render->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
	// Render->SetAlpha(120);
	// Render->SetAlpha();
	// Render->AddAlpha(-Delta * 255.0f);
}

void FadeObject::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void FadeObject::StateUpdate(float _Delta)
{
	switch (FadeValue)
	{
	case Fade::FadeOut:
		FadeOutUpdate(_Delta);
		break;
	case Fade::FadeIn: 
		FadeInUpdate(_Delta);
		break;
	default:
		break;
	}
}

void FadeObject::FadeOut()
{
	FadeValue = Fade::FadeOut; 
	Value = 0.0f;
}

void FadeObject::FadeOutUpdate(float _Delta)
{
	if (FadeDir)
	{
		Value += _Delta * 100;
		if (255.0f <= Value)
		{
			Death();
			return;
		}
		Render->SetAlpha(static_cast<unsigned char>(Value));
	}
}

void FadeObject::FadeIn()
{
	FadeValue = Fade::FadeIn;
	Value = 255.0f;
}

void FadeObject::FadeInUpdate(float _Delta)
{
	if (FadeDir)
	{
		Value -= _Delta * 100;
		if (0.0f >= Value)
		{
			Death();
			return;
		}
		Render->SetAlpha(static_cast<unsigned char>(Value));
	}
}