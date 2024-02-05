#pragma once
#include <EngineCore\Actor.h>

class ATitleKirby : public AActor
{
public:
	ATitleKirby();
	~ATitleKirby();

	ATitleKirby(const ATitleKirby& _Other) = delete;
	ATitleKirby(ATitleKirby&& _Other) noexcept = delete;
	ATitleKirby& operator=(const ATitleKirby& _Other) = delete;
	ATitleKirby& operator=(ATitleKirby&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer;
};