#pragma once
#include "Ability.h"

class AFire : public AAbility
{
public:
	AFire();
	~AFire();

	AFire(const AFire& _Other) = delete;
	AFire(AFire&& _Other) noexcept = delete;
	AFire& operator=(const AFire& _Other) = delete;
	AFire& operator=(AFire&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};