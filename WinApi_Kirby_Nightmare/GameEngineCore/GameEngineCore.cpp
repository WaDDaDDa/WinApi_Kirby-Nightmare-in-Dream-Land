#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>

// static �������� �ʱ�ȭ.
std::string GameEngineCore::WindowTitle = "";
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}

// ������ ����Ǹ� �Ͼ�� ��.
void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
    // �����ʿ� �غ� �� �ذ�
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
    GameEngineInput::InputInit();

    // ������ �غ� ���ش�. �غ�� �������� ����.
    Process->Start(); 
}
// ���� ������.
// �� ������Ʈ�� �ѹ����°��� �������̶�� �Ѵ�.
// �� �����ӵ����� ����� �⺻���� ���ÿ� ��ȭ�� �����Ϸ��� �����ǵ��� �ִ°�.
void GameEngineCore::CoreUpdate()
{
    if (nullptr != NextLevel)
    {
        if (nullptr != CurLevel)
        {
            CurLevel->LevelEnd(NextLevel);
            CurLevel->ActorLevelEnd();
        }

        NextLevel->LevelStart(CurLevel);
        NextLevel->ActorLevelStart();

        CurLevel = NextLevel;

        NextLevel = nullptr;
        GameEngineTime::MainTimer.Reset();
    }

    // �������� �ð��� �����ϱ� ���� ���⼭ Time Update�ϰ� DeltaTime�� �޾Ƶд�.
    GameEngineTime::MainTimer.Update();
    float Delta = GameEngineTime::MainTimer.GetDeltaTime();

    // �����쿡 ��Ŀ���� ���������� Ű�Է� �����ʰٴ�. 
    if (true == GameEngineWindow::IsFocus())
    {
        GameEngineInput::Update(Delta);
    }
    else
    {
        GameEngineInput::Reset();
    }

    CurLevel->AddLiveTime(Delta);
    CurLevel->Update(Delta);

    CurLevel->ActorUpdate(Delta);

    GameEngineWindow::MainWindow.ClearBackBuffer();
    CurLevel->ActorRender(Delta);
    CurLevel->Render();
    GameEngineWindow::MainWindow.DoubleBuffering();

    CurLevel->ActorRelease();
}
// ���� ������ ����.
void GameEngineCore::CoreEnd()
{
    Process->Release();

    // EngineStart���� �����Ҵ��� Process�� delete.
    if (nullptr != Process)
    {
        delete Process;
        Process = nullptr;
    }

    // CreateLevel���� �����Ҵ��� AllLevel�� Level���� ��ȸ�ϸ鼭 delete��.
    for (std::pair<std::string, GameEngineLevel*> _Pair : AllLevel)
    {
        if (nullptr != _Pair.second)
        {
            delete _Pair.second;
            _Pair.second = nullptr;
        }
    }
}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
    GameEngineDebug::LeckCheck();

    Process = _Ptr;
    WindowTitle = _Title;


    // CallBack ����̶�� �մϴ�. �Լ������͸� �̿�.
    // �����ϴ� ����� �Լ��� �̸������ϰ� ��������� ������ �Լ������͸� ����Ͽ�
    // ���߿� �ٸ� �Լ������ ���� �����Ҽ��ְ� �Ѵ�.
    GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
    _Level->Start();
}