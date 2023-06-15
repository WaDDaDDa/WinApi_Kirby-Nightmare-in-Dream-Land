#include "BurningKirby.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BackGround.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineCollision.h>

BurningKirby* BurningKirby::MainPlayer = nullptr;

BurningKirby::BurningKirby()
{

}

BurningKirby::~BurningKirby()
{

}

void BurningKirby::Start()
{
	// �ε� �Ǿ����� �ʴٸ� �ε��ϰ�, �ε� �Ǿ� �ִٸ� �ٽ� �ε����� �ʴ´�.
	// �ߺ� �ε��ϸ� ���� ��� �����.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("BurningKirbyLeft.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BurningKirbyLeft.bmp"), 7, 49);
		}
		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BurningKirbyRight.bmp"), 7, 49);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation ����
		MainRenderer->CreateAnimation("BurningKirbyLeft_Idle", "BurningKirbyLeft.bmp", 0, 6, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_DownIdle", "BurningKirbyLeft.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_Tackle", "BurningKirbyLeft.bmp", 80, 84, 0.1f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_Walk", "BurningKirbyLeft.bmp", 96, 105, 0.05f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Jump", "BurningKirbyLeft.bmp", 85, 85, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_JumpTurn", "BurningKirbyLeft.bmp", 87, 93, 0.03f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Falling", "BurningKirbyLeft.bmp", 94, 94, 1.0f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_FallingEnd", "BurningKirbyLeft.bmp", 95, 95, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Run", "BurningKirbyLeft.bmp", 0, 7, 0.1f, true);  // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("BurningKirbyLeft_Fly", "BurningKirbyLeft.bmp", 151, 158, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyLeft_BreathIn", "BurningKirbyLeft.bmp", 130, 134, 0.05f, true);
		MainRenderer->FindAnimation("BurningKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("BurningKirbyLeft_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("BurningKirbyLeft_AttackStart", "BurningKirbyLeft.bmp", 298, 300, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_Attack", "BurningKirbyLeft.bmp", 301, 320, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyLeft_BreathOut", "BurningKirbyLeft.bmp", 164, 165, 0.1f, false);
	}

	{ // RightAnimation ����
		MainRenderer->CreateAnimation("BurningKirbyRight_Idle", "BurningKirbyRight.bmp", 0, 4, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_Idle")->Inters[2] = 0.0f;
		MainRenderer->FindAnimation("BurningKirbyRight_Idle")->Inters[3] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyRight_DownIdle", "BurningKirbyRight.bmp", 8, 10, 0.2f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_DownIdle")->Inters[2] = 0.0f;
		MainRenderer->CreateAnimation("BurningKirbyRight_Tackle", "BurningKirbyRight.bmp", 80, 84, 0.1f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("BurningKirbyRight_Walk", "BurningKirbyRight.bmp", 96, 105, 0.05f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Jump", "BurningKirbyRight.bmp", 85, 85, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_JumpTurn", "BurningKirbyRight.bmp", 87, 93, 0.03f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_Falling", "BurningKirbyRight.bmp", 94, 94, 1.0f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_FallingEnd", "BurningKirbyRight.bmp", 95, 95, 0.1f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_Run", "BurningKirbyRight.bmp", 0, 7, 0.1f, true); // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("BurningKirbyRight_Fly", "BurningKirbyRight.bmp", 151, 158, 0.1f, true);
		MainRenderer->CreateAnimation("BurningKirbyRight_BreathIn", "BurningKirbyRight.bmp", 130, 134, 0.05f, true);
		MainRenderer->FindAnimation("BurningKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("BurningKirbyRight_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("BurningKirbyRight_AttackStart", "BurningKirbyRight.bmp", 298, 300, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_Attack", "BurningKirbyRight.bmp", 301, 320, 0.05f, false);
		MainRenderer->CreateAnimation("BurningKirbyRight_BreathOut", "BurningKirbyRight.bmp", 164, 165, 0.1f, false);
	}

	{ // �浹ü ����
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		AttackCollision = CreateCollision(CollisionOrder::SpecialAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::Rect);
		AttackCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);
	SetPos(float4{ 360,360 });
	SetAbillity(Abillity::Burning);
	// PlayerPos �� static ��� ���� ������ �ʱ� ��ġ�� �����ϰ� �����Ҽ�������.
	ChangeState(KirbyState::Idle);
}

void BurningKirby::Update(float _Delta)
{
	// �浹�Լ� �����.
	std::vector<GameEngineCollision*> _Col;

	if (true == BodyCollision->Collision(CollisionOrder::MonsterBody
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			//Actor->Death();
		}
	}

	// �� �� �ƿ� ���
	if (true == GameEngineInput::IsPress('L'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		// GameEngineLevel::CollisionDebugRenderSwitch();
	}


	StateUpdate(_Delta);

	CameraFocus(_Delta);
}

void BurningKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "BurningKirbyRight_";
		break;
	case KirbyDir::Left:
		AnimationName = "BurningKirbyLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void BurningKirby::CameraFocus(float _Delta)
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	int CameraRangeX = GetLevel()->GetMainCamera()->GetPos().iX();
	int CameraRangeY = GetLevel()->GetMainCamera()->GetPos().iY();

	int PlayerX = GetPos().iX();
	int PlayerY = GetPos().iY();

	float ImageX = GetGroundTexture()->GetScale().X - 960.0f;
	float ImageY = GetGroundTexture()->GetScale().Y;

	// ī�޶� ���� �������� ��������.
	if (0 >= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ 0.0f, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// ī�޶� ���� ������ �ִ�ġ�� ��������.
	if (ImageX <= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ ImageX, GetLevel()->GetMainCamera()->GetPos().Y });
	}

	if (0 >= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		//GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, 0.0f });
	}

	// ī�޶� �����̴� X ���� 250 ~ 650 ���̿�ĳ���͸� �д�.
	// ī�޶��� �ӵ��� ĳ������ �ӵ��� �Ѵ�.
	if (650 < PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({ Speed * _Delta , 0 });
	}
	else if (250 > PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({ -Speed * _Delta , 0 });
	}

	// ī�޶� �����̴� Y���� ĳ���Ͱ� -200 ~ -450 ���̿��� �����δ�.
	// ĳ���� �̵��ӵ��� ī�޶� ���� �������� �߷��� �ӵ��� �Ѵ�.
	if (-200 < CameraRangeY - PlayerY)
	{
		if (GetGravityVector().iY() <= -1)
		{
			GetLevel()->GetMainCamera()->AddPos(GetGravityVector() * _Delta);
			return;
		}
		GetLevel()->GetMainCamera()->AddPos(float4::UP);
	}
	else if (-450 > CameraRangeY - PlayerY)
	{
		if (GetGravityVector().iY() >= 1)
		{
			GetLevel()->GetMainCamera()->AddPos(GetGravityVector() * _Delta);
			return;
		}
		GetLevel()->GetMainCamera()->AddPos(float4::DOWN);
	}
}