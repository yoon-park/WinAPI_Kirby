#pragma once
#include "KirbyLevel.h"

class ULevel141 : public UKirbyLevel
{
public:
	ULevel141();
	~ULevel141();

	ULevel141(const ULevel141& _Other) = delete;
	ULevel141(ULevel141&& _Other) noexcept = delete;
	ULevel141& operator=(const ULevel141& _Other) = delete;
	ULevel141& operator=(ULevel141&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:

};