#pragma once
class Player
{
public:
    Player();
    ~Player();

    Player& operator=(const Player& _Other) = delete;
    Player& operator=(const Player&& _Other) = delete;
    Player(const Player& _Other) = delete;
    Player(const Player&& _Other) = delete;

protected:

private:

};

