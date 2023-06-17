#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

class Stage : public GameEngineActor
{
public:
    Stage();
    ~Stage();

    Stage(const Stage& _Other) = delete;
    Stage(Stage&& _Other) noexcept = delete;
    Stage& operator=(const Stage& _Other) = delete;
    Stage& operator=(Stage&& _Other) noexcept = delete;

    void Init(const std::string& _FileName, const std::string& _DebugFileName);

    void SwitchRender();

protected:

private:
    bool SwitchRenderValue = true;
    std::string FileName;
    std::string DebugFileName;
    class GameEngineRenderer* Renderer;
    class GameEngineRenderer* DebugRenderer;

    void Start() override;
    void Update(float _Delta) override;
    void Release() override;



};

