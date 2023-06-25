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
	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("IConName.bmp"), 4, 7);
	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HpBar.bmp"), 5, 3);

	IconUI = CreateUIRenderer(RenderOrder::PlayUI);
	IconUI->CreateAnimation("NormalKirbyIcon", "KirbyIcon.bmp", 0, 0, 0.1f, false);
	IconUI->CreateAnimation("SprkKirbyIcon", "KirbyIcon.bmp", 12, 12, 0.1f, false);
	IconUI->CreateAnimation("SwordKirbyIcon", "KirbyIcon.bmp", 22, 22, 0.1f, false);
	IconUI->CreateAnimation("BurningKirbyIcon", "KirbyIcon.bmp", 23, 23, 0.1f, false);
	IconUI->SetTexture("Blank.bmp");
	IconUI->SetRenderPos(IconPos);
	IconUI->SetScaleRatio(3.0f);
	IconUI->ChangeAnimation("NormalKirbyIcon");

	IconName = CreateUIRenderer(RenderOrder::PlayUI);
	IconName->CreateAnimation("NormalKirbyIconName", "IConName.bmp", 0, 0, 0.1f, false);
	IconName->CreateAnimation("SprkKirbyIconName", "IConName.bmp", 2, 2, 0.1f, false);
	IconName->CreateAnimation("SwordKirbyIconName", "IConName.bmp", 4, 4, 0.1f, false);
	IconName->CreateAnimation("BurningKirbyIconName", "IConName.bmp", 5, 5, 0.1f, false);
	IconName->SetTexture("Blank.bmp");
	IconName->SetRenderPos(IconNamePos);
	IconName->SetScaleRatio(3.0f);
	IconName->ChangeAnimation("NormalKirbyIconName");

	LifeIcon = CreateUIRenderer(RenderOrder::PlayUI);
	LifeIcon->CreateAnimation("KirbyLife", "HpBar.bmp", 0, 0, 0.1f, false);
	LifeIcon->SetTexture("Blank.bmp");
	LifeIcon->SetRenderPos(LifeIconPos);
	LifeIcon->SetScaleRatio(4.0f);
	LifeIcon->ChangeAnimation("KirbyLife");

	{ // 格见 10狼磊府
		LifeNum0 = CreateUIRenderer(RenderOrder::PlayUI);
		LifeNum0->CreateAnimation("KirbyLifeNum0_0", "HpBar.bmp", 3, 3, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_1", "HpBar.bmp", 4, 4, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_2", "HpBar.bmp", 5, 5, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_3", "HpBar.bmp", 6, 6, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_4", "HpBar.bmp", 7, 7, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_5", "HpBar.bmp", 8, 8, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_6", "HpBar.bmp", 9, 9, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_7", "HpBar.bmp", 10, 10, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_8", "HpBar.bmp", 11, 11, 0.1f, false);
		LifeNum0->CreateAnimation("KirbyLifeNum0_9", "HpBar.bmp", 12, 12, 0.1f, false);
		LifeNum0->SetTexture("Blank.bmp");
		LifeNum0->SetRenderPos(LifeNum0Pos);
		LifeNum0->SetScaleRatio(4.0f);
		LifeNum0->ChangeAnimation("KirbyLifeNum0_0");
	}

	{ // 格见 1狼磊府
		LifeNum = CreateUIRenderer(RenderOrder::PlayUI);
		LifeNum->CreateAnimation("KirbyLifeNum_0", "HpBar.bmp", 3, 3, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_1", "HpBar.bmp", 4, 4, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_2", "HpBar.bmp", 5, 5, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_3", "HpBar.bmp", 6, 6, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_4", "HpBar.bmp", 7, 7, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_5", "HpBar.bmp", 8, 8, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_6", "HpBar.bmp", 9, 9, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_7", "HpBar.bmp", 10, 10, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_8", "HpBar.bmp", 11, 11, 0.1f, false);
		LifeNum->CreateAnimation("KirbyLifeNum_9", "HpBar.bmp", 12, 12, 0.1f, false);
		LifeNum->SetTexture("Blank.bmp");
		LifeNum->SetRenderPos(LifeNumPos);
		LifeNum->SetScaleRatio(4.0f);
		LifeNum->ChangeAnimation("KirbyLifeNum_2");
	}
	// Hp bar
	{
		HpBar1 = CreateUIRenderer(RenderOrder::PlayUI);
		HpBar1->CreateAnimation("HpBar1On", "HpBar.bmp", 1, 1, 0.1f, false);
		HpBar1->CreateAnimation("HpBar1Off", "HpBar.bmp", 2, 2, 0.1f, false);
		HpBar1->SetTexture("Blank.bmp");
		HpBar1->SetRenderPos(HpBarPos);
		HpBar1->SetScaleRatio(4.0f);
		HpBar1->ChangeAnimation("HpBar1On");
	}

	{
		HpBar2 = CreateUIRenderer(RenderOrder::PlayUI);
		HpBar2->CreateAnimation("HpBar2On", "HpBar.bmp", 1, 1, 0.1f, false);
		HpBar2->CreateAnimation("HpBar2Off", "HpBar.bmp", 2, 2, 0.1f, false);
		HpBar2->SetTexture("Blank.bmp");
		HpBar2->SetRenderPos(HpBarPos + (HpBarInter));
		HpBar2->SetScaleRatio(4.0f);
		HpBar2->ChangeAnimation("HpBar2On");
	}
	{
		HpBar3 = CreateUIRenderer(RenderOrder::PlayUI);
		HpBar3->CreateAnimation("HpBar3On", "HpBar.bmp", 1, 1, 0.1f, false);
		HpBar3->CreateAnimation("HpBar3Off", "HpBar.bmp", 2, 2, 0.1f, false);
		HpBar3->SetTexture("Blank.bmp");
		HpBar3->SetRenderPos(HpBarPos + (HpBarInter * 2));
		HpBar3->SetScaleRatio(4.0f);
		HpBar3->ChangeAnimation("HpBar3On");
	}
	{
		HpBar4 = CreateUIRenderer(RenderOrder::PlayUI);
		HpBar4->CreateAnimation("HpBar4On", "HpBar.bmp", 1, 1, 0.1f, false);
		HpBar4->CreateAnimation("HpBar4Off", "HpBar.bmp", 2, 2, 0.1f, false);
		HpBar4->SetTexture("Blank.bmp");
		HpBar4->SetRenderPos(HpBarPos + (HpBarInter * 3));
		HpBar4->SetScaleRatio(4.0f);
		HpBar4->ChangeAnimation("HpBar4On");
	}
	{
		HpBar5 = CreateUIRenderer(RenderOrder::PlayUI);
		HpBar5->CreateAnimation("HpBar5On", "HpBar.bmp", 1, 1, 0.1f, false);
		HpBar5->CreateAnimation("HpBar5Off", "HpBar.bmp", 2, 2, 0.1f, false);
		HpBar5->SetTexture("Blank.bmp");
		HpBar5->SetRenderPos(HpBarPos + (HpBarInter * 4));
		HpBar5->SetScaleRatio(4.0f);
		HpBar5->ChangeAnimation("HpBar5On");
	}
	{
		HpBar6 = CreateUIRenderer(RenderOrder::PlayUI);
		HpBar6->CreateAnimation("HpBar6On", "HpBar.bmp", 1, 1, 0.1f, false);
		HpBar6->CreateAnimation("HpBar6Off", "HpBar.bmp", 2, 2, 0.1f, false);
		HpBar6->SetTexture("Blank.bmp");
		HpBar6->SetRenderPos(HpBarPos + (HpBarInter * 5));
		HpBar6->SetScaleRatio(4.0f);
		HpBar6->ChangeAnimation("HpBar6Off");
	}
	// 痢荐
	{
		ScoreNum0 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum0->CreateAnimation("ScoreNum0_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum0->CreateAnimation("ScoreNum0_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum0->SetTexture("Blank.bmp");
		ScoreNum0->SetRenderPos(ScoreNumPos);
		ScoreNum0->SetScaleRatio(4.0f);
		ScoreNum0->ChangeAnimation("ScoreNum0_0");
	}
	{
		ScoreNum1 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum1->CreateAnimation("ScoreNum1_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum1->CreateAnimation("ScoreNum1_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum1->SetTexture("Blank.bmp");
		ScoreNum1->SetRenderPos(ScoreNumPos + (ScoreNumInter * 1));
		ScoreNum1->SetScaleRatio(4.0f);
		ScoreNum1->ChangeAnimation("ScoreNum1_1");
	}
	{
		ScoreNum2 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum2->CreateAnimation("ScoreNum2_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum2->CreateAnimation("ScoreNum2_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum2->SetTexture("Blank.bmp");
		ScoreNum2->SetRenderPos(ScoreNumPos + (ScoreNumInter * 2));
		ScoreNum2->SetScaleRatio(4.0f);
		ScoreNum2->ChangeAnimation("ScoreNum2_2");
	}
	{
		ScoreNum3 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum3->CreateAnimation("ScoreNum3_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum3->CreateAnimation("ScoreNum3_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum3->SetTexture("Blank.bmp");
		ScoreNum3->SetRenderPos(ScoreNumPos + (ScoreNumInter * 3));
		ScoreNum3->SetScaleRatio(4.0f);
		ScoreNum3->ChangeAnimation("ScoreNum3_3");
	}
	{
		ScoreNum4 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum4->CreateAnimation("ScoreNum4_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum4->CreateAnimation("ScoreNum4_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum4->SetTexture("Blank.bmp");
		ScoreNum4->SetRenderPos(ScoreNumPos + (ScoreNumInter * 4));
		ScoreNum4->SetScaleRatio(4.0f);
		ScoreNum4->ChangeAnimation("ScoreNum4_4");
	}
	{
		ScoreNum5 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum5->CreateAnimation("ScoreNum5_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum5->CreateAnimation("ScoreNum5_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum5->SetTexture("Blank.bmp");
		ScoreNum5->SetRenderPos(ScoreNumPos + (ScoreNumInter * 5));
		ScoreNum5->SetScaleRatio(4.0f);
		ScoreNum5->ChangeAnimation("ScoreNum5_5");
	}
	{
		ScoreNum6 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum6->CreateAnimation("ScoreNum6_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum6->CreateAnimation("ScoreNum6_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum6->SetTexture("Blank.bmp");
		ScoreNum6->SetRenderPos(ScoreNumPos + (ScoreNumInter * 6));
		ScoreNum6->SetScaleRatio(4.0f);
		ScoreNum6->ChangeAnimation("ScoreNum6_6");
	}
	{
		ScoreNum7 = CreateUIRenderer(RenderOrder::PlayUI);
		ScoreNum7->CreateAnimation("ScoreNum7_0", "HpBar.bmp", 3, 3, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_1", "HpBar.bmp", 4, 4, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_2", "HpBar.bmp", 5, 5, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_3", "HpBar.bmp", 6, 6, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_4", "HpBar.bmp", 7, 7, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_5", "HpBar.bmp", 8, 8, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_6", "HpBar.bmp", 9, 9, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_7", "HpBar.bmp", 10, 10, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_8", "HpBar.bmp", 11, 11, 0.1f, false);
		ScoreNum7->CreateAnimation("ScoreNum7_9", "HpBar.bmp", 12, 12, 0.1f, false);
		ScoreNum7->SetTexture("Blank.bmp");
		ScoreNum7->SetRenderPos(ScoreNumPos + (ScoreNumInter * 7));
		ScoreNum7->SetScaleRatio(4.0f);
		ScoreNum7->ChangeAnimation("ScoreNum7_7");
	}

	SetAbillity(Abillity::Normal);
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
		IconName->ChangeAnimation("NormalKirbyIconName");
		break;
	case Abillity::Burning:
		IconUI->ChangeAnimation("BurningKirbyIcon");
		IconName->ChangeAnimation("BurningKirbyIconName");
		break;
	case Abillity::Spark:
		IconUI->ChangeAnimation("SparkKirbyIcon");
		IconName->ChangeAnimation("SprkKirbyIconName");
		break;
	case Abillity::Sword:
		IconUI->ChangeAnimation("SwordKirbyIcon");
		IconName->ChangeAnimation("SwordKirbyIconName");
		break;
	default:
		break;
	}

	SetAbillity(_Kirby);
}