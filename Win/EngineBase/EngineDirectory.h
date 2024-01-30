#pragma once
#include <list>

#include "EnginePath.h"

class UEngineFile;

class UEngineDirectory : public UEnginePath
{
public:
	UEngineDirectory();
	~UEngineDirectory();

	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

protected:

private:
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};