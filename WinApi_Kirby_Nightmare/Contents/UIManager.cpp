#include "UIManager.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>


UIManager* UIManager::UI = nullptr;

UIManager::UIManager()
{
	UI = this;
}

UIManager::~UIManager()
{
}

void UIManager::Start()
{
	GameEnginePath FilePath;
	FilePath.MoveParentToExistsChild("Resource");

	FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyIcon.bmp"), 4, 7);

	UIRenderer = CreateUIRenderer(RenderOrder::Play);
	UIRenderer->CreateAnimation("NormalKirby", "KirbyIcon.bmp", 0, 0, 0.2f, false);

	UIRenderer->SetRenderPos({ 50, 600 });
	UIRenderer->SetRenderScale({ 180, 180 });
	UIRenderer->ChangeAnimation("NormalKirby");
}