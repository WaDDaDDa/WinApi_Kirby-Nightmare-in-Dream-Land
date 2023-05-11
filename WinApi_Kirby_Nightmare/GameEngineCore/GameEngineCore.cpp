#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"

// static 변수들의 초기화.
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

// 게임이 실행되면 일어나는 일.
void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
    // 엔진쪽에 준비를 다 해고
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

    // 유저의 준비를 해준다. 준비된 컨텐츠의 실행.
    Process->Start(); 
}
// 게임 진행중.
// 이 업데이트가 한번도는것을 프레임이라고 한다.
// 한 프레임동안은 절대로 기본적인 셋팅에 변화가 없게하려고 설계의도가 있는것.
void GameEngineCore::CoreUpdate()
{
    if (nullptr != NextLevel)
    {
        CurLevel = NextLevel;
        NextLevel = nullptr;
        GameEngineTime::MainTimer.Reset();
    }

    // 프레임의 시간을 측정하기 위해 여기서 Time Update하고 DeltaTime을 받아둔다.
    GameEngineTime::MainTimer.Update();
    float Delta = GameEngineTime::MainTimer.GetDeltaTime();

    // Level에 있는 상속받은 업데이트하고 Level에 있는 Actor을 업데이트 한다.
    CurLevel->Update(Delta);

    CurLevel->ActorUpdate(Delta);

    GameEngineWindow::MainWindow.ClearBackBuffer();
    CurLevel->ActorRender();
    CurLevel->Render();
    GameEngineWindow::MainWindow.DoubleBuffering();

    CurLevel->ActorRelease();
}
// 게임 끝날때 정리.
void GameEngineCore::CoreEnd()
{
    Process->Release();

    // EngineStart에서 동적할당한 Process를 delete.
    if (nullptr != Process)
    {
        delete Process;
        Process = nullptr;
    }

    // CreateLevel에서 동적할당한 AllLevel의 Level들을 순회하면서 delete함.
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


    // CallBack 방식이라고 합니다. 함수포인터를 이용.
    // 대응하는 기능의 함수를 미리상정하고 만들수없기 때문에 함수포인터를 사용하여
    // 나중에 다른 함수기능을 만들어도 적용할수있게 한다.
    GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
    _Level->Start();
}