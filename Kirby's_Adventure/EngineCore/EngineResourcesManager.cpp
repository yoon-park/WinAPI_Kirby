#include "EngineResourcesManager.h"

#include "EngineBase\EngineDebug.h"
#include <EngineBase\EngineString.h>
#include <EnginePlatform\WindowImage.h>
#include "EngineCore.h"

UEngineResourcesManager::UEngineResourcesManager()
{

}

UEngineResourcesManager::~UEngineResourcesManager()
{
	for (std::pair<const std::string, UWindowImage*>& Pair : Images)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	Images.clear();
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();

	return LoadImg(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (Images.contains(UpperName) == true)
	{
		MsgBoxAssert(std::string("경로 : ") + std::string(_Path) + "파일명 : " + std::string(_Name) + "이미 로드한 파일을 다시 로드하려 했습니다.");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->Load(GEngine->MainWindow.GetWindowImage());

	Images[UpperName] = NewImage;

	return nullptr;
}

UWindowImage* UEngineResourcesManager::LoadFolder(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();

	return LoadFolder(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadFolder(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (Images.contains(UpperName) == true)
	{
		MsgBoxAssert(std::string("경로 : ") + std::string(_Path) + "파일명 : " + std::string(_Name) + "이미 로드한 파일을 다시 로드하려 했습니다.");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->LoadFolder(GEngine->MainWindow.GetWindowImage());

	Images[UpperName] = NewImage;

	return nullptr;
}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (Images.contains(UpperName) == false)
	{
		MsgBoxAssert("파일명 : " + std::string(_Name) + "은 존재하지 않는 이미지입니다");
		return nullptr;
	}

	return Images[UpperName];
}

void UEngineResourcesManager::CuttingImage(std::string_view _Name, int _X, int _Y)
{
	UWindowImage* FindImage = FindImg(_Name);

	if (FindImage == nullptr)
	{
		MsgBoxAssert("파일명 : " + std::string(_Name) + "존재하지 않는 이미지를 자르려고 했습니다.");
	}

	FindImage->Cutting(_X, _Y);
}