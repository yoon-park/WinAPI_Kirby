#pragma once
#include <EngineCore\Actor.h>

class AFire : public AActor
{
public:
	AFire();
	~AFire();

	AFire(const AFire& _Other) = delete;
	AFire(AFire&& _Other) noexcept = delete;
	AFire& operator=(const AFire& _Other) = delete;
	AFire& operator=(AFire&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	FVector Dir = FVector::Zero;
	float Speed = 500.0f;
};