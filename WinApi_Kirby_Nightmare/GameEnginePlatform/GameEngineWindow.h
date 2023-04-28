#pragma once
#include <Windows.h>
#include <string>

// 설명 :
class GameEngineWindow
{
public:
	// 윈도우창을 한개만 띄울것이기 때문에 MainWindow를 가지도록 선언.
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	// 윈도우 타이틀과 instance를 가지고 윈도우 창을 오픈하는 함수.
	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	inline HDC GetHDC()
	{
		return Hdc;
	}

protected:

private:
	// HInstance를 전역 멤버변수로 가진다.
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};

