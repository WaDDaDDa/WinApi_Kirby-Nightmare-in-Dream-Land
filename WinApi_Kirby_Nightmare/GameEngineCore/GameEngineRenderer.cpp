#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include "GameEngineCamera.h"
#include "ResourcesManager.h"
#include "GameEngineActor.h"
#include "GameEngineSprite.h"
#include "GameEngineLevel.h"
#include <math.h>

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetSprite(const std::string& _Name, size_t _Index/* = 0*/)
{
	Sprite = ResourcesManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 세팅하려고 했습니다." + _Name);
	}

	const GameEngineSprite::Sprite& SpriteInfo = Sprite->GetSprite(_Index);

	Texture = SpriteInfo.BaseTexture;

	SetCopyPos(SpriteInfo.RenderPos);
	SetCopyScale(SpriteInfo.RenderScale);

}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐를 세팅하려고 했습니다." + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

// 렌더 스케일을 이미지 그대로의 크기로 바꾸고 ScaleCheck를 False로 한다.
void GameEngineRenderer::SetRenderScaleToTexture()
{
	if (nullptr != Texture)
	{
		RenderScale = Texture->GetScale();
	}
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		// 1. 현재 프레임의 Inter가 0이되기 전에는
		CurAnimation->CurInter -= _DeltaTime;
		// 4. 현재 프레임의 Inter가 0보다 작거나 같아지면 
		if (0.0f >= CurAnimation->CurInter)
		{
			// 5. 현재프레임을 다음프레임으로 바꾼다.
			++CurAnimation->CurFrame;

			// 현재 애니메이션의 마지막 프레임번호 - 시작프레임 번호 가 현재의 프레임 번호 보다 작다면
			if (CurAnimation->CurFrame > abs(static_cast<int>(CurAnimation->EndFrame - CurAnimation->StartFrame)))
			{
				// 현재 프레임이 루프라면 처음부터 시작하도록 0으로.
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurFrame = 0;
				}
				else // 그게 아니면 이전 프레임으로 바꿔서 한다.
				{
					--CurAnimation->CurFrame;
				}
			}
			CurAnimation->CurInter
				= CurAnimation->Inters[CurAnimation->CurFrame];

		}

		// 2. 6. 현재 애니메이션의 프레임의 정보들을 얻어서
		size_t Frame = CurAnimation->Frames[CurAnimation->CurFrame];
		
		Sprite = CurAnimation->Sprite;
		const GameEngineSprite::Sprite& SpriteInfo = Sprite->GetSprite(Frame);
		Texture = SpriteInfo.BaseTexture;
		SetCopyPos(SpriteInfo.RenderPos);
		SetCopyScale(SpriteInfo.RenderScale);

		if (false == ScaleCheck)
		{
			SetRenderScale(SpriteInfo.RenderScale * ScaleRatio);
		}
	}

	if (nullptr == Texture)
	{
		MsgBoxAssert("이미지를 세팅하지 않은 랜더러 입니다.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	// 3. 7. 출력한다.
	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
	// BackBuffer->TransCopy(출력할 이미지, 출력될 엑터의 위치 + 출력될 이미지의 위치 - 카메라의 위치,
	//                          출력될 크기, 출력할 이미지의 시작점, 출력할 이미지의 끝점);

	// 카메라의 위치가 출력에 관여하는것 = 이동에 따른 카메라의 이동을 표현하기 위함.

}

bool GameEngineRenderer::IsDeath()
{
	// 랜더의 주체가되는 객체가 죽었다면 그것또한 렌더에게는 죽음이다.
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}

GameEngineRenderer::Animation* GameEngineRenderer::FindAnimation(const std::string& _AniamtionName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AniamtionName);

	std::map<std::string, Animation>::iterator FindIter = AllAnimation.find(UpperName);

	if (FindIter == AllAnimation.end())
	{
		return nullptr;
	}

	return &FindIter->second;
}

void GameEngineRenderer::CreateAnimation(
	const std::string& _AniamtionName, // 애니메이션 행동 이름
	const std::string& _SpriteName, // 스프라이트 이미지 이름
	size_t _Start /*= -1*/,  // 시작 프레임 
	size_t _End /*= -1*/,    // 끝 프레임
	float _Inter /*= 0.1f*/, // 프레임 전환 간격 시간 sec
	bool _Loop /*= true*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AniamtionName);

	if (nullptr != FindAnimation(UpperName))
	{
		MsgBoxAssert("이미 존재하는 애니메이션 네임입니다." + UpperName);
		return;
	}

	GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite(_SpriteName);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다." + _SpriteName);
		return;
	}

	GameEngineRenderer::Animation& Animation = AllAnimation[UpperName];

	Animation.Sprite = Sprite;

	if (_Start != -1)
	{
		Animation.StartFrame = _Start;
	}
	else
	{
		Animation.StartFrame = 0;
	}

	if (_End != -1)
	{
		Animation.EndFrame = _End;
	}
	else
	{
		Animation.EndFrame = Animation.Sprite->GetSpriteCount() - 1;
	}

	Animation.Inters.resize(abs(static_cast<int>(Animation.EndFrame - Animation.StartFrame)) + 1);
	Animation.Frames.resize(abs(static_cast<int>(Animation.EndFrame - Animation.StartFrame)) + 1);

	int FrameDir = 1;

	if (_Start > _End)
	{
		FrameDir = -1;
	}

	size_t Start = _Start;

	for (size_t i = 0; i < Animation.Inters.size(); i++)
	{
		Animation.Frames[i] = Start;
		Animation.Inters[i] = _Inter;
		Start += FrameDir;
	}

	Animation.Loop = _Loop;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _AniamtionName, bool _ForceChange/*= false*/)
{
	Animation* ChangeAnimation = FindAnimation(_AniamtionName);

	// 바꾸려는 애니메이션이 현재 애니메이션과 같고 ForceChange도 false라면 애니메이션 바꾸지않는다.
	if (ChangeAnimation == CurAnimation && false == _ForceChange)
	{
		return;
	}

	CurAnimation = FindAnimation(_AniamtionName);

	//애니메이션 바꾸고 처음부터 애니메이션 실행
	CurAnimation->CurInter = CurAnimation->Inters[0];
	CurAnimation->CurFrame = 0;

	if (nullptr == CurAnimation)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다." + _AniamtionName);
		return;
	}
}


void GameEngineRenderer::Start()
{
	Camera = Master->GetLevel()->GetMainCamera();
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 세팅되지 않았는데 오더를 지정했습니다.");
	}

	// 0 => 5번으로 바꾸고 싶다.

	// 오더를 변경하는건 마구잡이로 쓸만한건 아니다. 
	// 0번 랜더 그룹
	// 0번그룹에서는 삭제가 된다.
	std::list<GameEngineRenderer*>& PrevRenders = Camera->Renderers[GetOrder()];
	PrevRenders.remove(this);

	GameEngineObject::SetOrder(_Order);

	std::list<GameEngineRenderer*>& NextRenders = Camera->Renderers[GetOrder()];
	NextRenders.push_back(this);

}