#include "BossUIManager.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "Kirby.h"
#include "BossMonster.h"

BossUIManager* BossUIManager::BossUI = nullptr;

BossUIManager::BossUIManager()
{
	BossUI = this;
}

BossUIManager::~BossUIManager()
{

}

void BossUIManager::Start()
{
	GameEnginePath FilePath;
	FilePath.MoveParentToExistsChild("Resource");

	FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BossHpBar.bmp"), 11, 1);

	{
		BossHpBar = CreateUIRenderer(RenderOrder::PlayUI);
		BossHpBar->CreateAnimation("BossHp100", "BossHpBar.bmp", 0, 0, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp90", "BossHpBar.bmp", 1, 1, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp80", "BossHpBar.bmp", 2, 2, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp70", "BossHpBar.bmp", 3, 3, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp60", "BossHpBar.bmp", 4, 4, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp50", "BossHpBar.bmp", 5, 5, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp40", "BossHpBar.bmp", 6, 6, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp30", "BossHpBar.bmp", 7, 7, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp20", "BossHpBar.bmp", 8, 8, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp10", "BossHpBar.bmp", 9, 9, 0.1f, false);
		BossHpBar->CreateAnimation("BossHp0", "BossHpBar.bmp", 10, 10, 0.1f, false);
		BossHpBar->SetTexture("Blank.bmp");
		BossHpBar->SetRenderPos(BossHpPos);
		BossHpBar->SetScaleRatio(4.0f);
		BossHpBar->ChangeAnimation("BossHp100");
	}

	SetAbillity(Abillity::Normal);
}



void BossUIManager::Update(float _Delta)
{
	BossHpCheck();
}

void BossUIManager::BossHpCheck()
{
	if (BossMonster::GetBossHp() != CurBossHP)
	{
		CurBossHP = BossMonster::GetBossHp();

		int Value = CurBossHP / 10;

		switch (Value)
		{
		case 10:
			BossHpBar->ChangeAnimation("BossHp100");
			break;
		case 9:
			BossHpBar->ChangeAnimation("BossHp90");
			break;
		case 8:
			BossHpBar->ChangeAnimation("BossHp80");
			break;
		case 7:
			BossHpBar->ChangeAnimation("BossHp70");
			break;
		case 6:
			BossHpBar->ChangeAnimation("BossHp60");
			break;
		case 5:
			BossHpBar->ChangeAnimation("BossHp50");
			break;
		case 4:
			BossHpBar->ChangeAnimation("BossHp40");
			break;
		case 3:
			BossHpBar->ChangeAnimation("BossHp30");
			break;
		case 2:
			BossHpBar->ChangeAnimation("BossHp20");
			break;
		case 1:
			BossHpBar->ChangeAnimation("BossHp10");
			break;
		case 0:
			if (CurBossHP <= 0)
			{
				BossHpBar->ChangeAnimation("BossHp0");
			}
			break;
		default:
			BossHpBar->ChangeAnimation("BossHp0");
			break;
		}
	}
}