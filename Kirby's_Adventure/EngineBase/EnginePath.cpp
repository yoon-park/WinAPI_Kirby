#include "EnginePath.h"

#include <Windows.h>

#include "EngineDebug.h"

UEnginePath::UEnginePath()
	: Path(std::filesystem::current_path())
{

}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{

}

UEnginePath::~UEnginePath()
{

}

bool UEnginePath::IsFile()
{
	return !std::filesystem::is_directory(Path);
}

bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

std::string UEnginePath::GetExtension() const
{
	std::filesystem::path Text = Path.extension();

	return Text.string();
}

std::string UEnginePath::GetFileName() const
{
	std::filesystem::path Text = Path.filename();

	return Text.string();
}

std::string UEnginePath::AppendPath(std::string_view _Path)
{
	return Path.string() + "\\" + std::string(_Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void UEnginePath::Move(std::string_view _Path)
{
	std::filesystem::path NextPath = Path;
	NextPath.append(_Path);

	bool Check = std::filesystem::exists(NextPath);

	if (Check == false)
	{
		MsgBoxAssert(NextPath.string() + "��� ��δ� �������� �ʽ��ϴ�");
	}

	Path = NextPath;
}