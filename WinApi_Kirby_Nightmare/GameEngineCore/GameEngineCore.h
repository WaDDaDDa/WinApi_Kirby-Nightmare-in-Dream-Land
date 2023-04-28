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


class GameEngineLevel;
// ������ ����ü�� �˸� �ȵ����� ������ �ϴ°��� �����ټ��� �ִ�.
class GameEngineCore
{
public:
    GameEngineCore();
    ~GameEngineCore();

    GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
    GameEngineCore& operator=(const GameEngineCore&& _Other) = delete;
    GameEngineCore(const GameEngineCore& _Other) = delete;
    GameEngineCore(const GameEngineCore&& _Other) = delete;

	// template�� CoreProcessType�� �����ϰ� ������ ���μ����� �����ϴ� ����.
	template<typename CoreProcessType>
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst)
	{
		EngineStart(_Title, _Inst, new CoreProcessType());
	}

	// template�� cpp�� �����Ҽ� ����. ���ۿ����� �����ϸ� �˱⽱��.
	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		// �̹� ���ο� TitleLevel�� �����Ѵ�.
		if (AllLevel.end() != AllLevel.find(Upper))
		{
			// ���� Ÿ��Ʋ������ ������ Level�� �� �����Ƿ��� �Ѵٸ�.
			MsgBoxAssert(Upper + "�� �̸��� ���� GameEngineLevel�� �̹� �����մϴ�.");
			return;
		}

		// �̷��� CoreŬ������ �������� class���� �˰ԵǴ� �� �ƴѰ�?
		// �ƴϴ� template�� ������ ���� ���� ���� ���� �ڷ����� ���缭 �Լ��� �����ȴٰ� �����ִ�.
		GameEngineLevel* NewLevel = new LevelType();

		LevelInit(NewLevel);

		// make_pair�� map�� �� �� ����� �Լ�. �� ���� ����� insert�ؾ���.
		AllLevel.insert(std::make_pair(Upper, NewLevel));

		/* insert�Լ��� ��ȯ���� ��Ȯ�� �޾Ƽ� ����ϴ� ���.
		
		std::pair<std::map<std::string, class GameEngineLevel*>::iterator, bool> Pair 
			= AllLevel.insert(std::make_pair(_Title, nullptr));

		if (false == Pair.second)  Pair.second�� bool������ �ߺ����� �ƴ����� �Ǵ��ϴ� ����.
		{
			MsgBoxAssert("�̹� �����ϴ� �̸��� ������ �� ������� �߽��ϴ�" + _Title);
			return;
		}*/

	}

	// ȭ�鿡 ���� Level�� ���ϴ�.
	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, GameEngineLevel*>::iterator Finditer = AllLevel.find(Upper);

		// �̹� ���ο� TitleLevel�� �����Ѵ�.
		if (AllLevel.end() == Finditer)
		{
			MsgBoxAssert(Upper + "�� �̸��� ���� GameEngineLevel�� �������� �ʽ��ϴ�.");
			return;
		}

		// CurLevel�� �ٷ������ʴ� ������ Start�ܰ� �Ӹ��ƴ϶� Update�߰����� ChangeLevel�� �Ұ�쿡
		// �׼����� CurLevel�� �ٲ�� �����Ƿ� �Ѵܰ� ���İ��� NextLevel�� �غ��Ѵ�.
		NextLevel = Finditer->second;  // second���� GameEngineLevel*�� ����ִ�.
	}

protected:

private:
    static std::string WindowTitle;
	static CoreProcess* Process;

	// Core���� Level�� �𸣴»��·� �����ϰ� �;.
	static void LevelInit(GameEngineLevel* _Level); 

    // ������ ����Ǹ� �Ͼ�� ��.
    static void CoreStart(HINSTANCE _Inst);
    // ���� ������.
    static void CoreUpdate();
    // ���� ������ ����.
    static void CoreEnd();
    
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);

    // ���⼭ GameEngineLevel�� �𸣱⶧���� ���漱�� ���ش�.
    // map�ڷᱸ���� ����Ͽ� GameEngineLevel�� �����Ұ��̴�.
    static std::map<std::string, GameEngineLevel*> AllLevel;

	static GameEngineLevel* CurLevel;
	static GameEngineLevel* NextLevel;
};

