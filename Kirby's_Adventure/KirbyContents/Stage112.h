#pragma once
#include <EngineCore\Level.h>

class AFadeOut;

class UStage112 : public ULevel
{
public:
	UStage112();
	~UStage112();

	UStage112(const UStage112& _Other) = delete;
	UStage112(UStage112&& _Other) noexcept = delete;
	UStage112& operator=(const UStage112& _Other) = delete;
	UStage112& operator=(UStage112&& _Other) noexcept = delete;

protected:
	AFadeOut* Fade;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:

};