#include "FormChangeEffect.h"
#include <GameEngineCore/GameEngineRenderer.h>


FormChangeEffect::FormChangeEffect()
{

}

FormChangeEffect::~FormChangeEffect()
{

}



void FormChangeEffect::Start()
{
	Renderer = CreateRenderer(RenderOrder::Effect);
	Renderer->SetTexture("Blank.bmp");
	Renderer->SetScaleRatio(4.0f);
	SetPos(Kirby::GetMainPlayer()->GetPos());
	Renderer->CreateAnimation("FormChange", "FormChange.bmp", 0, 3, 0.1f, false);
	Renderer->ChangeAnimation("FormChange");
}

void FormChangeEffect::Update(float _Delta)
{
	SetPos(Kirby::GetMainPlayer()->GetPos());
	if (GetLiveTime() >= 0.6f)
	{
		Death();
	}
}
