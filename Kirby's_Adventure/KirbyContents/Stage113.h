#pragma once
#include <EngineCore\Level.h>

class UStage113 : public ULevel
{
public:
	UStage113();
	~UStage113();

	UStage113(const UStage113& _Other) = delete;
	UStage113(UStage113&& _Other) noexcept = delete;
	UStage113& operator=(const UStage113& _Other) = delete;
	UStage113& operator=(UStage113&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:

};