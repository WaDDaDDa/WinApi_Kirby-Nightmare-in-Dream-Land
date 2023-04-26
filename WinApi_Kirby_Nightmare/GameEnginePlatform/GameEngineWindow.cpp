#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>

// static으로 선언된 Instance 변수를 null로 초기화. 이후 Opne되면 내프로그램의 Instance를 받게됨.
HINSTANCE GameEngineWindow::Instance = nullptr;
// 윈도우창을 한개만 띄울것이기 때문에 MainWindow를 가지도록 선언.
GameEngineWindow GameEngineWindow::MainWindow;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
    // 공통의 instance를 사용하므로 static으로 선언된 변수를 사용.
    Instance = _hInstance;
    // 오픈할때 인자로 입력한 문자열을 Title로 가진다.
    Title = _Title;

    if (nullptr == Instance)
    {
        MsgBoxAssert("HInstance없이 윈도우를 만들수는 없습니다.");
        return;
    }
    //윈도우 등록단계
    MyRegisterClass();
    // 윈도우 create하고 띄우는 단계
    InitInstance();
}


void GameEngineWindow::InitInstance()
{
    // 윈도우 만드는 함수인
    // const char* == std::string
    // "DefaultWindow" 로 등록된 윈도우를 크리에이트 한다.
    // Title.c_str() 은 std::string 자료형인 Title을 std::string의 .c_str()을 사용하여 char* 로 형변환 해준것.
    hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("윈도우 생성에 실패했습니다.");
        return;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(_hWnd, message, wParam, lParam);
    }
    return 0;
}

// 띄울 윈도우 창을 등록한다
void GameEngineWindow::MyRegisterClass()
{
    static bool Check = false;

    // 윈도우 창이 2번 등록되는것을 방지하기 위한 Local static변수
    if (true == Check)
    {
        return;
    }

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // LRESULT(CALLBACK* WNDPROC)(HWND, unsigned int, unsigned int, unsigned int);
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow"; // 등록할 윈도우를 "DeafaultWindow"로 불러내야한다.
    wcex.hIconSm = nullptr;

    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("윈도우 클래스 동록에 실패했습니다.");
        return;
    }

    Check = true;
}

// 메세지 루프를 시작, 업데이트, 엔드로 나누어서 우리가 만들 게임에 적용하기 적합하도록 설계.
void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    // 윈도우가 뜨기전에 로딩해야할 이미지나 사운드 등등을 처리하는 단계
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 업데이트 단계.
        if (nullptr != _Update)
        {
            _Update();
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 마무리 단계
    if (nullptr != _End)
    {
        _End();
    }


    // (int)msg.wParam;

    return;
}