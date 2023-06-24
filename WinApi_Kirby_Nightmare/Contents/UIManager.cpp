#include "UIManager.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "Kirby.h"


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
	UIRenderer->CreateAnimation("NormalKirbyIcon", "KirbyIcon.bmp", 0, 0, 0.1f, false);
	UIRenderer->CreateAnimation("SprkKirbyIcon", "KirbyIcon.bmp", 12, 12, 0.1f, false);
	UIRenderer->CreateAnimation("SwordKirbyIcon", "KirbyIcon.bmp", 22, 22, 0.1f, false);
	UIRenderer->CreateAnimation("BurningKirbyIcon", "KirbyIcon.bmp", 23, 23, 0.1f, false);

	UIRenderer->SetRenderPos({ 50, 600 });
	UIRenderer->SetRenderScale({ 180, 180 });
	SetAbillity(Abillity::Normal);
	UIRenderer->ChangeAnimation("NormalKirbyIcon");
}

void UIManager::Update(float _Delta)
{
	if (GetAbillity() != Kirby::GetMainPlayer()->GetAbillity())
	{
		IconChange(Kirby::GetMainPlayer()->GetAbillity());
	}
}

void UIManager::IconChange(Abillity _Kirby)
{
	switch (_Kirby)
	{
	case Abillity::Normal:
		UIRenderer->ChangeAnimation("NormalKirbyIcon");
		break;
	case Abillity::Burning:
		UIRenderer->ChangeAnimation("BurningKirbyIcon");
		break;
	case Abillity::Spark:
		UIRenderer->ChangeAnimation("SparkKirbyIcon");
		break;
	case Abillity::Sword:
		UIRenderer->ChangeAnimation("SwordKirbyIcon");
		break;
	default:
		break;
	}

	SetAbillity(_Kirby);
}