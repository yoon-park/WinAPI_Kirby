#pragma once
#include <string>
#include <string_view>

#include "ThirdParty\FMOD\inc\fmod.hpp"

class UEngineSound
{
public:
	UEngineSound();
	~UEngineSound();

	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view _Path, std::string_view _Name);

protected:

private:
	FMOD::Sound* SoundHandle = nullptr;
};

