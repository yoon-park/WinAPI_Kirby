#pragma once
#include "KirbyActor.h"

class AHUD : public AKirbyActor
{
public:
	AHUD();
	~AHUD();

	AHUD(const AHUD& _Other) = delete;
	AHUD(AHUD&& _Other) noexcept = delete;
	AHUD& operator=(const AHUD& _Other) = delete;
	AHUD& operator=(AHUD&& _Other) noexcept = delete;

	void SetHUDImage(std::string_view _MapImageName);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer;
};