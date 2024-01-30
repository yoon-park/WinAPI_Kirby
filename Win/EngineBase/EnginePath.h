#pragma once
#include <string>
#include <filesystem>

class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	bool IsFile();
	bool IsDirectory();

	bool IsExists();

	void MoveParent();
	void Move(std::string_view _Path);

protected:
	std::filesystem::path Path;

private:

};