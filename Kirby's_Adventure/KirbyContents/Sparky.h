#pragma once
#include "Monster.h"

class ASparky : public AMonster
{
public:
	ASparky();
	~ASparky();

	ASparky(const ASparky& _Other) = delete;
	ASparky(ASparky&& _Other) noexcept = delete;
	ASparky& operator=(const ASparky& _Other) = delete;
	ASparky& operator=(ASparky&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveStart() override;
	void Move(float _DeltaTime) override;

private:

};