#pragma once
#include <Windows.h>
#include <string>

// ���� :
class GameEngineWindow
{
public:
	// ������â�� �Ѱ��� �����̱� ������ MainWindow�� �������� ����.
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	// ������ Ÿ��Ʋ�� instance�� ������ ������ â�� �����ϴ� �Լ�.
	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	inline HDC GetHDC()
	{
		return Hdc;
	}

protected:

private:
	// HInstance�� ���� ��������� ������.
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};

