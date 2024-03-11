#pragma once
#include "KirbyLevel.h"

class ULevel111 : public UKirbyLevel
{
public:
	ULevel111();
	~ULevel111();

	ULevel111(const ULevel111& _Other) = delete;
	ULevel111(ULevel111&& _Other) noexcept = delete;
	ULevel111& operator=(const ULevel111& _Other) = delete;
	ULevel111& operator=(ULevel111&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:

};