#pragma once
#include "Monster.h"

class ABrontoBurt : public AMonster
{
public:
	ABrontoBurt();
	~ABrontoBurt();

	ABrontoBurt(const ABrontoBurt& _Other) = delete;
	ABrontoBurt(ABrontoBurt&& _Other) noexcept = delete;
	ABrontoBurt& operator=(const ABrontoBurt& _Other) = delete;
	ABrontoBurt& operator=(ABrontoBurt&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void UpDownDirCheck() override;

	void MoveStart() override;
	void Move(float _DeltaTime) override;

private:

};