#pragma once
#include <Windows.h>
#include <string>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

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

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	float4 GetScale()
	{
		return Scale;
	}

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

protected:

private:
	// HInstance를 전역 멤버변수로 가진다.
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;
	static bool IsWindowUpdate; // 윈도우가 종료되기 위한 변수.

	// 윈도우가 생성될때 가지는 Texture. 이것이 가지는 이미지가 변경될때마다 출력되는 이미지가 달라짐.
	GameEngineWindowTexture* BackBuffer = nullptr;
	float4 Scale;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();

};

