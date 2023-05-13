#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>

// static���� ����� Instance ������ null�� �ʱ�ȭ. ���� Opne�Ǹ� �����α׷��� Instance�� �ްԵ�.
HINSTANCE GameEngineWindow::Instance = nullptr;
// ������â�� �Ѱ��� �����̱� ������ MainWindow�� �������� ����.
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
    // ������ instance�� ����ϹǷ� static���� ����� ������ ���.
    Instance = _hInstance;
    // �����Ҷ� ���ڷ� �Է��� ���ڿ��� Title�� ������.
    Title = _Title;

    if (nullptr == Instance)
    {
        MsgBoxAssert("HInstance���� �����츦 ������� �����ϴ�.");
        return;
    }
    //������ ��ϴܰ�
    MyRegisterClass();
    // ������ create�ϰ� ���� �ܰ�
    InitInstance();
}

// ��ϵ� �����츦 �����ϰ� ����.
void GameEngineWindow::InitInstance()
{
    // ������ ����� �Լ���
    // const char* == std::string
    // "DefaultWindow" �� ��ϵ� �����츦 ũ������Ʈ �Ѵ�.
    // Title.c_str() �� std::string �ڷ����� Title�� std::string�� .c_str()�� ����Ͽ� char* �� ����ȯ ���ذ�.
    hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("������ ������ �����߽��ϴ�.");
        return;
    }
    // �׸������� ������ GetDC��� �Լ��� ���� �޾ƺ����ִ�.
    Hdc = GetDC(hWnd);

    // �����찡 �����ɶ� GameEngineWindowTexture���� �����Ǿ� Hdc�� �޾��ش�.
    // �����쿡 ��µǰԵ� �̹���
    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc);

    // ���� �۹����� �ϱ����� �̹���. �ѹ��� �����쿡 ��½�Ű������ ����� �̹����� �̸� �׷����� ĵ����.
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

// ��� ������ â�� ����Ѵ�
void GameEngineWindow::MyRegisterClass()
{
    static bool Check = false;

    // ������ â�� 2�� ��ϵǴ°��� �����ϱ� ���� Local static����
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
    wcex.lpszClassName = "DefaultWindow"; // ����� �����츦 "DeafaultWindow"�� �ҷ������Ѵ�.
    wcex.hIconSm = nullptr;

    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("������ Ŭ���� ���Ͽ� �����߽��ϴ�.");
        return;
    }

    Check = true;
}

// �޼��� ������ ����, ������Ʈ, ����� ����� �츮�� ���� ���ӿ� �����ϱ� �����ϵ��� ����.
// �Լ� �����͸� ����Ͽ� �Լ��� ���ڷ� �޾Ƽ� ����Ҽ� �ִ�.
void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    // �����찡 �߱����� �ε��ؾ��� �̹����� ���� ����� ó���ϴ� �ܰ�
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;

    while (IsWindowUpdate) // false�Ǹ� ������ �����.
    {
        // �����쿡 �������� �ִ°� �ƴ϶� �޼����� �ֵ� ����
        // �����Լ� _getch()
        // <= Ű�� ���������� �����
        // (�Լ��� ����� ���������� ��ٸ��� �Լ����� ���� �Լ���� �մϴ�).
        // GetMessage�� ���� �Լ�����. �������� �޼����� �߻��Ҷ����� ��ٸ���.
        // �񵿱� �޼��� �Լ��� �ִ�. 
        // PeekMessage�� ������ �޼����� ������ 0�� ���ϵǰ� �׳� �����մϴ�.

        // �����Ӱ� ����Ÿ���� �ϼ��ƴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // �޼����� ������ ������Ʈ�� �ϰ�.
            if (nullptr != _Update)
            {
                _Update();
            }
            // �޼����� ó���ϰ�.
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue; // �Ʒ��κ��� ������Ʈ�� �ǳʶڴ�.
        }

        // ������ �޼����� ���� �ð��� ����Ÿ���̶�� �մϴ�.
        // ������ ����Ÿ�ӿ� ���ư��°� �����̴�.
        // �����߿� 2���� ������ �ִ�. �����츦 �����̰ų� ũ�⸦ ���̸�
        // ȭ���� �����ϴ� ����. 
        // ���� �׷� ������ �޼����� �߻���Ű�� ���߿��� ������ ��� ���ư��� �����ִ�.

        // �̰� �ѹٲ ���� ���� ������
        // FPS
        // �ʴ� ȭ���� �׷����� Ƚ��
        // �ϵ����͵� ������ �ִ�.
        if (nullptr != _Update)
        {
            // �޼����� ��� ������Ʈ�� �Ѵ�.
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

// �������� Ÿ��Ʋ�� Ȥ�� �׵θ��� ũ�⸦ ����� ������ ũ�⸦ ������ְ� ���ִ� �Լ�.
// ������ Ÿ��Ʋ�� ��� ũ�Ⱑ �ִµ� �׳� �����츦 �����ϰ� �ȴٸ� �׸����� ������ ũ�⸦ �����ϰ� �ǹǷ� 
// ���ϴ� �ػ� ������ �ȳ����� ��Ȳ�� ����� ���� �����ϱ� ����.
void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
    // Window���� LP �����Ͷ�� �� Long Pointer
    Scale = _Scale;

    // BackBuffer�� �̹������ϸ� ����� �ٽ� �����Ѵ�.
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