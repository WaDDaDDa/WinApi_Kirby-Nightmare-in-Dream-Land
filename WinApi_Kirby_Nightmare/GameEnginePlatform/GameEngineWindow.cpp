#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>

// static으로 선언된 Instance 변수를 null로 초기화. 이후 Opne되면 내프로그램의 Instance를 받게됨.
HINSTANCE GameEngineWindow::Instance = nullptr;
// 윈도우창을 한개만 띄울것이기 때문에 MainWindow를 가지도록 선언.
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = false;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = nullptr;
    }

    if (nullptr != WindowBuffer)
    {
        delete WindowBuffer;
        WindowBuffer = nullptr;
    }
}

void GameEngineWindow::ClearBackBuffer()
{
    Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
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

// 등록된 윈도우를 생성하고 띄운다.
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
    // 그리기위한 권한을 GetDC라는 함수를 통해 받아볼수있다.
    Hdc = GetDC(hWnd);

    // 윈도우가 생성될때 GameEngineWindowTexture또한 생성되어 Hdc를 받아준다.
    // 윈도우에 출력되게될 이미지
    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc);

    // 더블 퍼버링을 하기위한 이미지. 한번에 윈도우에 출력시키기위해 출력할 이미지를 미리 그려놓은 캔버스.
    BackBuffer = new GameEngineWindowTexture();
    BackBuffer->ResCreate(WindowBuffer->GetScale());

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

void GameEngineWindow::DoubleBuffering()
{
    WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SETFOCUS:
    {
        IsFocusValue = true;
        return DefWindowProc(_hWnd, message, wParam, lParam);
    }
    case WM_KILLFOCUS:
    {
        IsFocusValue = false;
        return DefWindowProc(_hWnd, message, wParam, lParam);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        // PostQuitMessage(0);
        IsWindowUpdate = false;
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
// 함수 포인터를 사용하여 함수를 인자로 받아서 사용할수 있다.
void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    // 윈도우가 뜨기전에 로딩해야할 이미지나 사운드 등등을 처리하는 단계
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;

    while (IsWindowUpdate) // false되면 루프가 종료됨.
    {
        // 윈도우에 무슨일이 있는게 아니라 메세지가 있든 없든
        // 동기함수 _getch()
        // <= 키가 눌릴때까지 멈춘다
        // (함수가 제대로 끝날때까지 기다리는 함수들을 동기 함수라고 합니다).
        // GetMessage는 동기 함수에요. 윈도우의 메세지가 발생할때까지 기다린다.
        // 비동기 메세지 함수가 있다. 
        // PeekMessage는 윈도우 메세지가 없으면 0이 리턴되고 그냥 리턴합니다.

        // 프레임과 데드타임이 완성됐다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 메세지가 있을때 업데이트를 하고.
            if (nullptr != _Update)
            {
                _Update();
            }
            // 메세지를 처리하고.
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue; // 아래부분의 업데이트는 건너뛴다.
        }

        // 윈도우 메세지가 없는 시간을 데드타임이라고 합니다.
        // 게임은 데드타임에 돌아가는게 보통이다.
        // 게임중에 2가지 종류가 있다. 윈도우를 움직이거나 크기를 줄이면
        // 화면이 정지하는 게임. 
        // 내가 그런 윈도우 메세지를 발생시키는 와중에도 게임은 계속 돌아가는 게임있다.

        // 이게 한바뀌가 도는 것을 프레임
        // FPS
        // 초당 화면이 그려지는 횟수
        // 하드웨어와도 연결이 있다.
        if (nullptr != _Update)
        {
            // 메세지가 없어도 업데이트를 한다.
            _Update();
        }

    }

    if (nullptr != _End)
    {
        _End();
    }
    // (int)msg.wParam;

    return;
}

// 윈도우의 타이틀바 혹은 테두리의 크기를 고려한 윈도우 크기를 만들수있게 해주는 함수.
// 윈도우 타이틀바 등에도 크기가 있는데 그냥 윈도우를 생성하게 된다면 그모든것을 포함한 크기를 설정하게 되므로 
// 원하는 해상도 배율이 안나오는 상황이 생기는 것을 방지하기 위함.
void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
    // Window에서 LP 포인터라는 뜻 Long Pointer
    Scale = _Scale;

    // BackBuffer가 이미존재하면 지우고 다시 생성한다.
    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = new GameEngineWindowTexture();
        BackBuffer->ResCreate(Scale);
    }

    //                200           200
    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };


    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    //                          100        100         500          500
    SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}