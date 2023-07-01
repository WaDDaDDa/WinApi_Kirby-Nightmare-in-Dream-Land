#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "BGMPlayer.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Untitled.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Backgrounds\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Untitled.bmp"), 2, 1);
		}

		{
			//����Ʈ �ε�
			FilePath.MoveParentToExistsChild("Resource");
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("DamageEffects.bmp"), 3, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Star.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("StarEffects.bmp"), 4, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RightCharge.bmp"), 3, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LeftCharge.bmp"), 3, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BunringMonsterAttack.bmp"), 6, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FireEffect1Left.bmp"), 7, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FireEffect2Left.bmp"), 7, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FireEffect1Right.bmp"), 7, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FireEffect2Right.bmp"), 7, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BunringMonsterAttack.bmp"), 6, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Blank.bmp"), 4, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkEffect.bmp"), 4, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Effect1.bmp"), 7, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LeftSwordEffect.bmp"), 8, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RightSwordEffect.bmp"), 8, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WoodAtt.bmp"), 5, 4);

		}
	}
	// ���� �ε�
	if (nullptr == GameEngineSound::FindSound("01Main_Title.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("01Main_Title.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("06 Ice Cream Island.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("20 Boss Battle.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song105.wav")); // ������ ���󰡴� ����
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song111.wav")); // Ǫ�� ���ߴ���
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song114.wav")); // ��ȫ ���� ���
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song115.wav")); // ���� ����
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song116.wav")); // ���� ƨ��´���
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song120.wav")); // �ǿ� fly

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song128.wav")); // Ǫ�ƾƾ� �һձ�
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song137.wav")); // Ǫ�ƾƾ� �� ��һձ�

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song145.wav")); // Ǫ�� Į ���(�ǰ�)
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song147.wav")); // Ǫ�� Į ���(���)
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song154.wav")); // ����ũ ���� ���
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song173.wav")); // ��Ŭ����
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song181.wav")); // ��η� ������ �Ա�
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song215.wav")); // �s ��������
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song220.wav")); // ���+1
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song222.wav")); // ������
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song223.wav")); // ���ݱ�
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song227.wav")); // ����������
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song260.wav")); // bosshit
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song528.wav")); // ����������

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song539.wav")); // Ŀ�� ������� 1
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song103.wav")); // Ŀ�� ������� 2

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song540.wav")); // Ŀ�� ��׷���
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song545.wav")); // ������ ����ũ ����
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song579.wav")); // �������
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song580.wav")); // ��� ����

	}

	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("Untitled.Bmp");
	CurBackGround->SetAnimation("Title", "Untitled.Bmp", 0, 1, 0.2f, true);

	CurBackGround->SetPos({480,300});

	BGMPlayer::SetBGM("01Main_Title.mp3");
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P') ||
		true == GameEngineInput::IsDown('Q') ||
		true == GameEngineInput::IsDown('W') ||
		true == GameEngineInput::IsDown('E') ||
		true == GameEngineInput::IsDown('R') ||
		true == GameEngineInput::IsDown('T') ||
		true == GameEngineInput::IsDown('Y') ||
		true == GameEngineInput::IsDown('U') ||
		true == GameEngineInput::IsDown('I') ||
		true == GameEngineInput::IsDown('O') ||
		true == GameEngineInput::IsDown('A') ||
		true == GameEngineInput::IsDown('S') ||
		true == GameEngineInput::IsDown('D') ||
		true == GameEngineInput::IsDown('F') ||
		true == GameEngineInput::IsDown('G') ||
		true == GameEngineInput::IsDown('H') ||
		true == GameEngineInput::IsDown('J') ||
		true == GameEngineInput::IsDown('L') ||
		true == GameEngineInput::IsDown('Z') ||
		true == GameEngineInput::IsDown('X') ||
		true == GameEngineInput::IsDown('C') ||
		true == GameEngineInput::IsDown('V') ||
		true == GameEngineInput::IsDown('B') ||
		true == GameEngineInput::IsDown('N') ||
		true == GameEngineInput::IsDown('M'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
	}
}
