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

	IconUI = CreateUIRenderer(RenderOrder::Play);
	IconUI->CreateAnimation("NormalKirbyIcon", "KirbyIcon.bmp", 0, 0, 0.1f, false);
	IconUI->CreateAnimation("SprkKirbyIcon", "KirbyIcon.bmp", 12, 12, 0.1f, false);
	IconUI->CreateAnimation("SwordKirbyIcon", "KirbyIcon.bmp", 22, 22, 0.1f, false);
	IconUI->CreateAnimation("BurningKirbyIcon", "KirbyIcon.bmp", 23, 23, 0.1f, false);
	IconUI->SetTexture("Blank.bmp");
	IconUI->SetRenderPos(IconPos);
	IconUI->SetScaleRatio(3.0f);
	//IconUI->SetRenderScale(IconScale);
	SetAbillity(Abillity::Normal);
	IconUI->ChangeAnimation("NormalKirbyIcon");
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
		IconUI->ChangeAnimation("NormalKirbyIcon");
		break;
	case Abillity::Burning:
		IconUI->ChangeAnimation("BurningKirbyIcon");
		break;
	case Abillity::Spark:
		IconUI->ChangeAnimation("SparkKirbyIcon");
		break;
	case Abillity::Sword:
		IconUI->ChangeAnimation("SwordKirbyIcon");
		break;
	default:
		break;
	}

	SetAbillity(_Kirby);
}