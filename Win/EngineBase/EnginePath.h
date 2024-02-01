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

	std::string GetFullPath() const
	{
		return Path.string();
	}

	std::string GetExtension() const;
	std::string GetFileName() const;

	std::string AppendPath(std::string_view _Path);

	void MoveParent();
	void Move(std::string_view _Path);

protected:
	std::filesystem::path Path;

private:

};