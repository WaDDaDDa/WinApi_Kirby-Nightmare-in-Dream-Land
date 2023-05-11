#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime()
{
	// 1초에 해당하는 카운트를 받아준다. QueryPerformanceFrequency()
	QueryPerformanceFrequency(&Count);
	// 프로그램이 실행되자마자 시간이 흐르는것을 Time이 생성될때 리셋해준다.
	Reset();
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	// 지금까지 카운트를 얼마나 세었는지. QueryPerformanceCounter()
	QueryPerformanceCounter(&Cur);
	Prev = Cur;  // Prev와 Cur을 같게하니깐 현재와 이전의 차이가 없어서 흐른시간을 0으로보는것.
}

// 프레임 사이에서 실행되어야할 함수들은 다 업데이트라고 이름을 지을 것이다.
// Time의 Update는 update가 실행되는동안의 시간을 구하는 함수이다.
void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur); // Reset이후 Cur에 현재 퍼포먼스시간을 받아주니 prev와 cur의차이가 생김
	// 이는 곳 reset이후 흐른 시간이 됨.
	// Tick 은 현재시간 - 이전시간 으로 업데이트가 되기까지 걸린시간을 담는다.
	Tick = Cur.QuadPart - Prev.QuadPart;

	// 이 값을 Count로 나누어주면 실제 흐른 시간이 된다.  double은 8바이트 실수형으로 더 정확한값이 가능.
	// 하지만 느려서 정확성을 아주 신경쓰는 경우가 아니면 사용하지 않을 예정.
	// 8바이트 실수형                  사이값        /          셀수있는 시간
	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart; // 한번 1Tick에 대한 시간을 구한후에 리셋해준것이다.
	FloatDelta = static_cast<float>(DoubleDelta);
}