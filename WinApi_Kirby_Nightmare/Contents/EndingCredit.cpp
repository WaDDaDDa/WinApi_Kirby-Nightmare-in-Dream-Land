#include "EndingCredit.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "Kirby.h"
#include "BossMonster.h"

EndingCredit* EndingCredit::EndingUI = nullptr;

EndingCredit::EndingCredit()
{
	EndingUI = this;
}

EndingCredit::~EndingCredit()
{

}

void EndingCredit::Start()
{
	GameEnginePath FilePath;
	FilePath.MoveParentToExistsChild("Resource");

	FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Ending.bmp"), 1, 1);

	{
		Render = CreateUIRenderer(RenderOrder::PlayUI);
		Render->SetTexture("Blank.bmp");
		Render->CreateAnimation("EndingCredit", "Ending.bmp", 0, 0, 0.1f, false);
		Render->SetRenderPos(RenderPos);
		Render->SetScaleRatio(3.8f);
		Render->ChangeAnimation("EndingCredit");
	}
}



void EndingCredit::Update(float _Delta)
{
	RenderPos = RenderPos + float4::UP * 100 * _Delta;

	if (RenderPos.Y <= -600.0f )
	{
		RenderPos = { 480.0f, -600.0f };
	}

	Render->SetRenderPos(RenderPos);
}
