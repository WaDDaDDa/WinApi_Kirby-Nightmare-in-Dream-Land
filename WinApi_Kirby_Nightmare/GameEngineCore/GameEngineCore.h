#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>
#include <string>
#include <map>
#include "GameEngineObject.h"

class CoreProcess : public GameEngineObject
{

};


// 컨텐츠 그자체를 알면 안되지만 관리를 하는것을 도와줄수는 있다.
class GameEngineLevel;
class GameEngineCore
{
public:

	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	// template로 CoreProcessType을 지정하고 지정한 프로세스를 시작하는 원리.
	template<typename CoreProcessType>
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst)
	{
		EngineStart(_Title, _Inst, new CoreProcessType());
	}

	// template는 cpp에 구현할수 없다. 동작원리를 생각하면 알기쉽다.
	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() != AllLevel.find(Upper))
		{
			// 같은 타이틀네임을 가지는 Level이 또 생성되려고 한다면.
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 이미 존재합니다.");
			return;
		}

		// 이러면 Core클래스가 컨텐츠의 class들을 알게되는 것 아닌가?
		// 아니다 template의 문법상 직접 사용된 곳에 사용된 자료형에 맞춰서 함수가 생성된다고 볼수있다.
		GameEngineLevel* NewLevel = new LevelType();

		LevelInit(NewLevel);

		// make_pair는 map에 들어갈 페어를 만드는 함수. 페어를 먼저 만들고 insert해야함.
		AllLevel.insert(std::make_pair(Upper, NewLevel));

	}

	// 화면에 보일 Level을 정하는.
	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, GameEngineLevel*>::iterator Finditer = AllLevel.find(Upper);

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() == Finditer)
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 존재하지 않습니다.");
			return;
		}

		// CurLevel로 바로하지않는 이유는 Start단계 뿐만아니라 Update중간에도 ChangeLevel을 할경우에
		// 그순간에 CurLevel이 바뀌어 버리므로 한단계 거쳐가는 NextLevel을 준비한다.
		NextLevel = Finditer->second;  // second에는 GameEngineLevel*가 들어있다.
	}

	static GameEngineLevel* GetNextLevel()
	{
		return NextLevel;
	}

protected:

private:
    static std::string WindowTitle;
	static CoreProcess* Process;

	// Core에서 Level을 모르는상태로 관리하고 싶어서.
	static void LevelInit(GameEngineLevel* _Level); 

    // 게임이 실행되면 일어나는 일.
    static void CoreStart(HINSTANCE _Inst);
    // 게임 진행중.
    static void CoreUpdate();
    // 게임 끝날때 정리.
    static void CoreEnd();
    
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);

    // 여기서 GameEngineLevel을 모르기때문에 전방선언 해준다.
    // map자료구조를 사용하여 GameEngineLevel을 관리할것이다.
    static std::map<std::string, GameEngineLevel*> AllLevel;

	static GameEngineLevel* CurLevel;
	static GameEngineLevel* NextLevel;

	GameEngineCore();
	~GameEngineCore();
};

