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
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = false;
	bool IsEnd = false;

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
	
	FTransform GetRenderTransForm();

	UWindowImage* GetImage() const
	{
		return Image;
	}

	int GetCurAnimationFrame() const
	{
		return CurAnimation->CurFrame;
	}

	int GetCurAnimationImageFrame() const
	{
		const std::vector<int>& Indexs = CurAnimation->Indexs;
		return Indexs[CurAnimation->CurFrame];
	}

	float GetCurAnimationTime() const
	{
		return CurAnimation->CurTime;
	}

	bool IsCurAnimationEnd() const
	{
		return CurAnimation->IsEnd;
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

	void SetAngle(float _Angle)
	{
		Angle = _Angle;
	}

	void SetOrder(int _Order) override;
	void SetImage(std::string_view _Name, int _InfoIndex = 0);

	void SetText(std::string_view _Text)
	{
		Text = _Text;
	}
	void SetFont(std::string_view _Font)
	{
		Font = _Font;
	}
	void SetTextSize(float _Value)
	{
		Size = _Value;
	}
	void SetTextColor(Color8Bit _Color)
	{
		TextColor = _Color;
	}
	void SetCameraRatio(float _Ratio)
	{
		CameraRatio = _Ratio;
	}

	void CameraEffectOff()
	{
		CameraEffect = false;
	}

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool _Loop = true
	);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		std::vector<int> _Indexs,
		float _Inter,
		bool _Loop = true
	);

	void ChangeAnimation(
		std::string_view _AnimationName,
		bool _IsForce = false,
		int _StartIndex = 0,
		float _Time = -1.0f
	);
	
	void AnimationReset();

	void Render(float _DeltaTime);
	void ImageRender(float _DeltaTime);
	void TextRender(float _DeltaTime);

protected:
	void BeginPlay() override;

private:
	int InfoIndex = 0;
	FTransform ImageCuttingTransform;
	Color8Bit TransColor;
	float Angle = 0.0f;
	UWindowImage* Image = nullptr;

	std::string Text = "";
	std::string Font = "±Ã¼­";
	float Size = 10.0f;
	Color8Bit TextColor = Color8Bit::BlackA;

	bool CameraEffect = true;
	float CameraRatio = 1.0f;
	UAnimationInfo* CurAnimation = nullptr;

	std::map<std::string, UAnimationInfo> AnimationInfos;
};