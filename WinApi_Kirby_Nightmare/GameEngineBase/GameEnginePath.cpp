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
	// �����̸��� ���ڿ��� ����
	return Path.filename().string();
}

void GameEnginePath::GetCurrentPath()
{
	// ���� ��θ� Path�� ����.
	Path = std::filesystem::current_path();
}


void GameEnginePath::MoveParent()
{
	// �Ѵܰ����� ��θ� Path�� ����.
	Path = Path.parent_path();
}

// ���ڿ� ã�����ϴ� �����̸��� �־ ���������������� ã���鼭 ������ �� ���������� ��� �̵�.
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
			MsgBoxAssert("��Ʈ ��α��� ������ ��������" + _ChildPath + "�����̳� ������ ������ ������ �ִ� ��θ� ã�� ���߽��ϴ�");
		}
	}


}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�." + CheckPath.string());
	}

	Path = CheckPath;
	// Path.append(_ChildPath);
}