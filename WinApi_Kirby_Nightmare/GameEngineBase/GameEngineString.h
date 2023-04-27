#pragma once
#include <string>

// 문자열에 관련된 모든것을 할 예정.
class GameEngineString
{
public:
    GameEngineString();
    ~GameEngineString();

    GameEngineString& operator=(const GameEngineString& _Other) = delete;
    GameEngineString& operator=(const GameEngineString&& _Other) = delete;
    GameEngineString(const GameEngineString& _Other) = delete;
    GameEngineString(const GameEngineString&& _Other) = delete;

	// 문자를 전부 대문자로 만들어준다.
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

