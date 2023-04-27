#include "GameEngineCore.h"

// static �������� �ʱ�ȭ.
std::string GameEngineCore::WindowTitle = "";
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel;

GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}

// ������ ����Ǹ� �Ͼ�� ��.
void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
}
// ���� ������.
void GameEngineCore::CoreUpdate()
{

}
// ���� ������ ����.
void GameEngineCore::CoreEnd()
{

}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst)
{
    GameEngineDebug::LeckCheck();
    // CallBack ����̶�� �մϴ�. �Լ������͸� �̿�.
    // �����ϴ� ����� �Լ��� �̸������ϰ� ��������� ������ �Լ������͸� ����Ͽ�
    // ���߿� �ٸ� �Լ������ ���� �����Ҽ��ְ� �Ѵ�.
    WindowTitle = _Title;
    GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}