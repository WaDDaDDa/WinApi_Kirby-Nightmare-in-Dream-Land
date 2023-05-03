#pragma once
#include <string>

// 게임에 관한 모든 리소스는 해당 객체에서 직접 로드해주고 언로드해주는 방식이 제일 좋다.
// 리소스가 이미 로드되어있으면 건너뛰고 없으면 로드한다.
// 레벨이 바뀌게 된다면 모든 리소스를 전부 언로드하고 다시 있어야할 리소스들만 로드하는 방식.

// 또는 레벨이 바뀌어도 쓰이게될 리소스는 언로드하지않고 유지한채 로드하는 방법도있는데
// 하기나름이다. 고민을 해볼것.


// 설명 : 선생님이 마지막으로 알려주는 싱글톤
// 보통 UML과 함께 배우는것이 좋다.
// 생성 구분에 해당
// 생성 객체를 생성하는 방법을 
// 패턴 소양 정도로만 알고있으면 됩니다.
// 이 프로그램에서 이 객체가 1개만 있었으면 좋겠다.
class GameEngineTexture;
class ResourcesManager
{
public:
	// delete Function
	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	// 3. 리턴해준다.
	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	//static ResourcesManager* GetInst()
	//{
	//	if (nullptr == Inst)
	//	{
	//		Inst = new ResourcesManager();
	//	}
	//	return Inst;
	//}

	//static void ResetInst() 
	//{
	//	if (nullptr != Inst)
	//	{
	//		delete Inst;
	//  Inst = new ResourcesManager();
	//}

	//static void Destroy() 
	//{
	//	if (nullptr != Inst)
	//	{
	//		delete Inst;
	//	}
	//}

	// 파일명이 곧 찾기위한 이름이 된다.
	void TextureLoad(const std::string& _Path)
	{
		// _Path 파일명

		// TextureLoad();
	}

	void TextureLoad(const std::string& _Name, const std::string& _Path)
	{

	}

	GameEngineTexture* FindTexture(const std::string& _Image);
	bool IsLoadTexture(const std::string& _Image);


protected:

private:
	// 2. 내부에 static 포인터든 값이든 뭐든 1개를 둔다.
	static ResourcesManager Inst;

	// static ResourcesManager* Inst;

	// 1. 생성자를 private안에 넣는다.
	ResourcesManager();
	~ResourcesManager();


};

