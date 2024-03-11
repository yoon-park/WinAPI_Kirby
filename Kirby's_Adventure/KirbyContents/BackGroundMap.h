#pragma once
#include <EngineCore\Actor.h>

class ABackGroundMap : public AActor
{
public:
	ABackGroundMap();
	~ABackGroundMap();

	ABackGroundMap(const ABackGroundMap& _Other) = delete;
	ABackGroundMap(ABackGroundMap&& _Other) noexcept = delete;
	ABackGroundMap& operator=(const ABackGroundMap& _Other) = delete;
	ABackGroundMap& operator=(ABackGroundMap&& _Other) noexcept = delete;

	FVector GetImageScale()
	{
		return ImageScale;
	}

	void SetMapImage(std::string_view _MapImageName);
	void SetColMapImage(std::string_view _MapImageName);

	void SwitchDebug();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* ColRenderer = nullptr;
	FVector ImageScale;
};
