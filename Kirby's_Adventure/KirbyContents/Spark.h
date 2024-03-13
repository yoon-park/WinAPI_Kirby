#pragma once
#include "Ability.h"

class ASpark : public AAbility
{
public:
	ASpark();
	~ASpark();

	ASpark(const ASpark& _Other) = delete;
	ASpark(ASpark&& _Other) noexcept = delete;
	ASpark& operator=(const ASpark& _Other) = delete;
	ASpark& operator=(ASpark&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};