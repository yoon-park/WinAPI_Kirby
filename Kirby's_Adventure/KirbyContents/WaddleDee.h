#pragma once
#include "Monster.h"

class AWaddleDee : public AMonster
{
public:
	AWaddleDee();
	~AWaddleDee();

	AWaddleDee(const AWaddleDee& _Other) = delete;
	AWaddleDee(AWaddleDee&& _Other) noexcept = delete;
	AWaddleDee& operator=(const AWaddleDee& _Other) = delete;
	AWaddleDee& operator=(AWaddleDee&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};