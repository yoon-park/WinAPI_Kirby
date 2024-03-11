#pragma once
#include "KirbyLevel.h"

class ULevel113 : public UKirbyLevel
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

};