#pragma once
#include <string>
#include <EngineCore/Level.h>

class ABackGroundMap;
class AFadeOut;

class UKirbyLevel : public ULevel
{
public:
	UKirbyLevel();
	~UKirbyLevel();

	UKirbyLevel(const UKirbyLevel& _Other) = delete;
	UKirbyLevel(UKirbyLevel&& _Other) noexcept = delete;
	UKirbyLevel& operator=(const UKirbyLevel& _Other) = delete;
	UKirbyLevel& operator=(UKirbyLevel&& _Other) noexcept = delete;

	std::string GetNextLevel()
	{
		return NextLevel;
	}

	void SetNextLevel(std::string _NextLevel)
	{
		NextLevel = _NextLevel;
	}

protected:
	ABackGroundMap* Map;
	AFadeOut* Fade;

private:
	std::string NextLevel = "";
};