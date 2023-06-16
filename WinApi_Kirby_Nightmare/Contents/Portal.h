#pragma once
class Portal
{
public:
    Portal();
    ~Portal();

    Portal(const Portal& _Other) = delete;
    Portal(Portal&& _Other) noexcept = delete;
    Portal& operator=(const Portal& _Other) = delete;
    Portal& operator=(Portal&& _Other) noexcept = delete;

protected:

private:

};

