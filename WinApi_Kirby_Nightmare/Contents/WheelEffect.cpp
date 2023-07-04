#include "WheelEffect.h"
#include <GameEngineCore/GameEngineRenderer.h>


WheelEffect::WheelEffect()
{

}

WheelEffect::~WheelEffect()
{

}

void WheelEffect::Start()
{
	LeftRenderer = CreateRenderer(RenderOrder::BackEffect);
	LeftRenderer->SetTexture("Blank.bmp");
	LeftRenderer->SetScaleRatio(4.0f);
	SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ 100.0f , 0.0f });
	LeftRenderer->CreateAnimation("LeftEffect", "WheelKirbyLeft.bmp", 232, 232, 0.1f, false);


	LeftRenderer2 = CreateRenderer(RenderOrder::BackEffect2);
	LeftRenderer2->SetTexture("Blank.bmp");
	LeftRenderer2->SetScaleRatio(4.0f);
	SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ 200.0f , 0.0f });
	LeftRenderer2->CreateAnimation("LeftEffect2", "WheelKirbyLeft.bmp", 233, 233, 0.1f, false);

	RightRenderer = CreateRenderer(RenderOrder::BackEffect);
	RightRenderer->SetTexture("Blank.bmp");
	RightRenderer->SetScaleRatio(4.0f);
	SetPos(Kirby::GetMainPlayer()->GetPos() - float4{ 200.0f , 0.0f });
	RightRenderer->CreateAnimation("RightEffect", "WheelKirbyRight.bmp", 232, 232, 0.1f, false);


	RightRenderer2 = CreateRenderer(RenderOrder::BackEffect2);
	RightRenderer2->SetTexture("Blank.bmp");
	RightRenderer2->SetScaleRatio(4.0f);
	SetPos(Kirby::GetMainPlayer()->GetPos() - float4{ 100.0f , 0.0f });
	RightRenderer2->CreateAnimation("RightEffect2", "WheelKirbyRight.bmp", 233, 233, 0.1f, false);

	if (Kirby::GetMainPlayer()->GetDir() == KirbyDir::Left)
	{
		LeftRenderer->ChangeAnimation("LeftEffect");
		LeftRenderer2->ChangeAnimation("LeftEffect2");
	}
	else if (Kirby::GetMainPlayer()->GetDir() == KirbyDir::Right)
	{
		RightRenderer->ChangeAnimation("RightEffect");
		RightRenderer2->ChangeAnimation("RightEffect2");
	}

}

void WheelEffect::Update(float _Delta)
{
	SetPos(Kirby::GetMainPlayer()->GetPos());
}
