#pragma once
#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"

class UWindowImage;

class UImageRenderer : public USceneComponent
{
public:
	UImageRenderer();
	~UImageRenderer();

	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	void SetImage(std::string_view _Name, bool _IsImageScale = false);
	void SetImageToScale(std::string_view _Name);
	void SetOrder(int _Order) override;

	void Render(float _DeltaTime);

protected:
	void BeginPlay() override;

private:
	UWindowImage* Image;
};

