#include <GameEnginePlatform/GameEngineWindow.h>
#include <iostream>

// 게임이 실행되면 일어나는 일.
void TestStart(HINSTANCE _Inst)
{
    GameEngineWindow::MainWindow.Open("MainWindow", _Inst);
}
// 게임 진행중.
void TestUpdate()
{

}
// 게임 끝날때 정리.
void TestEnd()
{

}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // CallBack 방식이라고 합니다.
    GameEngineWindow::MessageLoop(hInstance, TestStart, TestUpdate, TestEnd);
    return 0;
}