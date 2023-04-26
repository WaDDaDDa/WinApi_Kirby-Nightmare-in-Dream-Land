#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>

// static���� ����� Instance ������ null�� �ʱ�ȭ. ���� Opne�Ǹ� �����α׷��� Instance�� �ްԵ�.
HINSTANCE GameEngineWindow::Instance = nullptr;
// ������â�� �Ѱ��� �����̱� ������ MainWindow�� �������� ����.
GameEngineWindow GameEngineWindow::MainWindow;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
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
void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    // �����찡 �߱����� �ε��ؾ��� �̹����� ���� ����� ó���ϴ� �ܰ�
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // ������Ʈ �ܰ�.
        if (nullptr != _Update)
        {
            _Update();
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ������ �ܰ�
    if (nullptr != _End)
    {
        _End();
    }


    // (int)msg.wParam;

    return;
}