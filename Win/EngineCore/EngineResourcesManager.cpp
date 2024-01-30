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
		MsgBoxAssert(std::string("��� : ") + std::string(_Path) + "���ϸ� : " + std::string(_Name) + "�̹� �ε��� ������ �ٽ� �ε��Ϸ� �߽��ϴ�.");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->Load(GEngine->MainWindow.GetWindowImage());

	Images[UpperName] = NewImage;

	return nullptr;
}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (Images.contains(UpperName) == false)
	{
		MsgBoxAssert("���ϸ� : " + std::string(_Name) + "�� �������� �ʴ� �̹����Դϴ�");
		return nullptr;
	}

	return Images[UpperName];
}