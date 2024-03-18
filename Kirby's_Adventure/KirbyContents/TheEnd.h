#pragma once
#include "KirbyActor.h"

class ATheEnd : public AKirbyActor
{
public:
	ATheEnd();
	~ATheEnd();

	ATheEnd(const ATheEnd& _Other) = delete;
	ATheEnd(ATheEnd&& _Other) noexcept = delete;
	ATheEnd& operator=(const ATheEnd& _Other) = delete;
	ATheEnd& operator=(ATheEnd&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;

};