#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime()
{
	// 1�ʿ� �ش��ϴ� ī��Ʈ�� �޾��ش�. QueryPerformanceFrequency()
	QueryPerformanceFrequency(&Count);
	// ���α׷��� ������ڸ��� �ð��� �帣�°��� Time�� �����ɶ� �������ش�.
	Reset();
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	// ���ݱ��� ī��Ʈ�� �󸶳� ��������. QueryPerformanceCounter()
	QueryPerformanceCounter(&Cur);
	Prev = Cur;  // Prev�� Cur�� �����ϴϱ� ����� ������ ���̰� ��� �帥�ð��� 0���κ��°�.
}

// ������ ���̿��� ����Ǿ���� �Լ����� �� ������Ʈ��� �̸��� ���� ���̴�.
// Time�� Update�� update�� ����Ǵµ����� �ð��� ���ϴ� �Լ��̴�.
void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur); // Reset���� Cur�� ���� �����ս��ð��� �޾��ִ� prev�� cur�����̰� ����
	// �̴� �� reset���� �帥 �ð��� ��.
	// Tick �� ����ð� - �����ð� ���� ������Ʈ�� �Ǳ���� �ɸ��ð��� ��´�.
	Tick = Cur.QuadPart - Prev.QuadPart;

	// �� ���� Count�� �������ָ� ���� �帥 �ð��� �ȴ�.  double�� 8����Ʈ �Ǽ������� �� ��Ȯ�Ѱ��� ����.
	// ������ ������ ��Ȯ���� ���� �Ű澲�� ��찡 �ƴϸ� ������� ���� ����.
	// 8����Ʈ �Ǽ���                  ���̰�        /          �����ִ� �ð�
	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart; // �ѹ� 1Tick�� ���� �ð��� �����Ŀ� �������ذ��̴�.
	FloatDelta = static_cast<float>(DoubleDelta);
}