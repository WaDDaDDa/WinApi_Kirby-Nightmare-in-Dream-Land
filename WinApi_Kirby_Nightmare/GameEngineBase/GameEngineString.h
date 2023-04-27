#pragma once
#include <string>

// ���ڿ��� ���õ� ������ �� ����.
class GameEngineString
{
public:
    GameEngineString();
    ~GameEngineString();

    GameEngineString& operator=(const GameEngineString& _Other) = delete;
    GameEngineString& operator=(const GameEngineString&& _Other) = delete;
    GameEngineString(const GameEngineString& _Other) = delete;
    GameEngineString(const GameEngineString&& _Other) = delete;

	// ���ڸ� ���� �빮�ڷ� ������ش�.
	static std::string ToUpperReturn(const std::string& _Value)
	{
		std::string UpperString = _Value;

		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}

		return UpperString;
	}

protected:

private:

};

