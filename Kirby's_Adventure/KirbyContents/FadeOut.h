#pragma once
#include "KirbyActor.h"

enum class FadeOption
{
	FadeIn,
	FadeOut,
};

class AFadeOut : public AKirbyActor
{
public:
	AFadeOut();
	~AFadeOut();

	AFadeOut(const AFadeOut& _Other) = delete;
	AFadeOut(AFadeOut&& _Other) noexcept = delete;
	AFadeOut& operator=(const AFadeOut& _Other) = delete;
	AFadeOut& operator=(AFadeOut&& _Other) noexcept = delete;

	void FadeStart(FadeOption _Option)
	{
		switch (_Option)
		{
		case FadeOption::FadeOut:
			Renderer->SetAlpha(0.0f);
			Dir = 1.0f;
			FadeValue = 0.0f;
			break;
		case FadeOption::FadeIn:
			Renderer->SetAlpha(1.0f);
			Dir = -1.0f;
			FadeValue = 1.0f;
			break;
		default:
			break;
		}

		StartFade = true;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	float Dir = 1.0f;
	float FadeValue = 1.0f;
	bool StartFade = false;
};