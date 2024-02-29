#pragma once
#include <EngineCore\Level.h>

class AFadeOut;

class ULevel113 : public ULevel
{
public:
	ULevel113();
	~ULevel113();

	ULevel113(const ULevel113& _Other) = delete;
	ULevel113(ULevel113&& _Other) noexcept = delete;
	ULevel113& operator=(const ULevel113& _Other) = delete;
	ULevel113& operator=(ULevel113&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:
	AFadeOut* Fade;
};