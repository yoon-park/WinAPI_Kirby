#pragma once
#include <map>

#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"

class UWindowImage;

class UAnimationInfo
{
public:
	UWindowImage* Image = nullptr;
	std::string Name;
	int Start = -1;
	int End = -1;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = false;

	std::vector<float> Times;
	std::vector<int> Indexs;

	int Update(float _DeltaTime);
};

class UImageRenderer : public USceneComponent
{
public:
	UImageRenderer();
	~UImageRenderer();

	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;
	
	UWindowImage* GetImage() const
	{
		return Image;
	}

	void SetImageIndex(int _InfoIndex)
	{
		InfoIndex = _InfoIndex;
	}

	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTransform(_Value);
	}

	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

	void SetTransColor(Color8Bit _Color)
	{
		TransColor = _Color;
	}

	void SetAlpha(float _Alpha)
	{
		if (_Alpha <= 0.0f)
		{
			_Alpha = 0.0f;
		}

		if (_Alpha >= 1.0f)
		{
			_Alpha = 1.0f;
		}

		TransColor.A = static_cast<char>(_Alpha * 255.0f);
	}

	void SetOrder(int _Order) override;
	void SetImage(std::string_view _Name, int _InfoIndex = 0);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName, bool _IsForce = false);
	void AnimationReset();

	void Render(float _DeltaTime);

protected:
	void BeginPlay() override;

private:
	int InfoIndex = 0;
	FTransform ImageCuttingTransform;
	Color8Bit TransColor;
	UWindowImage* Image = nullptr;
	UAnimationInfo* CurAnimation = nullptr;

	std::map<std::string, UAnimationInfo> AnimationInfos;
};