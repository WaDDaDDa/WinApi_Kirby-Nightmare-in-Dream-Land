#include "GameEngineCore.h"

// static 변수들의 초기화.
std::string GameEngineCore::WindowTitle = "";
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel;

GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}

// 게임이 실행되면 일어나는 일.
void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
}
// 게임 진행중.
void GameEngineCore::CoreUpdate()
{

}
// 게임 끝날때 정리.
void GameEngineCore::CoreEnd()
{

}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst)
{
    GameEngineDebug::LeckCheck();
    // CallBack 방식이라고 합니다. 함수포인터를 이용.
    // 대응하는 기능의 함수를 미리상정하고 만들수없기 때문에 함수포인터를 사용하여
    // 나중에 다른 함수기능을 만들어도 적용할수있게 한다.
    WindowTitle = _Title;
    GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}