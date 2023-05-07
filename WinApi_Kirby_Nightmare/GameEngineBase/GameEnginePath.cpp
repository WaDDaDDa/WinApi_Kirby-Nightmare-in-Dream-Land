#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::string& _path)
	: Path(_path)
{

}

GameEnginePath::~GameEnginePath()
{
}

std::string GameEnginePath::GetFileName()
{
	// 파일이름을 문자열로 리턴
	return Path.filename().string();
}

void GameEnginePath::GetCurrentPath()
{
	// 현재 경로를 Path에 저장.
	Path = std::filesystem::current_path();
}


void GameEnginePath::MoveParent()
{
	// 한단계위의 경로를 Path에 저장.
	Path = Path.parent_path();
}

// 인자에 찾고자하는 파일이름을 넣어서 상위폴더에서부터 찾으면서 없으면 또 상위폴더로 계속 이동.
void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert("루트 경로까지 샅샅히 뒤졌지만" + _ChildPath + "파일이나 폴더를 하위로 가지고 있는 경로를 찾지 못했습니다");
		}
	}


}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로로 이동하려고 했습니다." + CheckPath.string());
	}

	Path = CheckPath;
	// Path.append(_ChildPath);
}