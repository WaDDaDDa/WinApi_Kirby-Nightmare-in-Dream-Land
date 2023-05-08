#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

class Stage : public GameEngineActor
{
public:
    Stage();
    ~Stage();

    Stage& operator=(const Stage& _Other) = delete;
    Stage& operator=(const Stage&& _Other) = delete;
    Stage(const Stage& _Other) = delete;
    Stage(const Stage&& _Other) = delete;

    void Init(const std::string& _FileName);

protected:

private:

    std::string FileName;

    void Start() override;
    void Update(float _Delta) override;
    void Render() override;
    void Release() override;



};

