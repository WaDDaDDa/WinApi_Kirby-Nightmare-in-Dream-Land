#pragma once

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineString.h>
#include <map>
#include <string>

class GameEngineLevel;
// 컨텐츠 그자체를 알면 안되지만 관리를 하는것을 도와줄수는 있다.
class GameEngineCore
{
public:
    GameEngineCore();
    ~GameEngineCore();

    GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
    GameEngineCore& operator=(const GameEngineCore&& _Other) = delete;
    GameEngineCore(const GameEngineCore& _Other) = delete;
    GameEngineCore(const GameEngineCore&& _Other) = delete;

    static void EngineStart(const std::string& _Title, HINSTANCE _Inst);

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

		// make_pair는 map에 들어갈 페어를 만드는 함수. 페어를 먼저 만들고 insert해야함.
		AllLevel.insert(std::make_pair(Upper, NewLevel));

		/* insert함수의 반환값을 정확히 받아서 사용하는 방식.
		
		std::pair<std::map<std::string, class GameEngineLevel*>::iterator, bool> Pair 
			= AllLevel.insert(std::make_pair(_Title, nullptr));

		if (false == Pair.second)  Pair.second가 bool값으로 중복인지 아닌지를 판단하는 값임.
		{
			MsgBoxAssert("이미 존재하는 이름의 레벨을 또 만들려고 했습니다" + _Title);
			return;
		}*/

	}

protected:

private:

    // 게임이 실행되면 일어나는 일.
    static void CoreStart(HINSTANCE _Inst);
    // 게임 진행중.
    static void CoreUpdate();
    // 게임 끝날때 정리.
    static void CoreEnd();
    
    static std::string WindowTitle;

    // 여기서 GameEngineLevel을 모르기때문에 전방선언 해준다.
    // map자료구조를 사용하여 GameEngineLevel을 관리할것이다.
    static std::map<std::string, GameEngineLevel*> AllLevel;
};

