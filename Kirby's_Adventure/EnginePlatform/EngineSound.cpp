#include "EngineSound.h"

#ifdef _DEBUG	
#pragma comment(lib, "ThirdParty\\FMOD\\inc\\fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

UEngineSound::UEngineSound()
{

}

UEngineSound::~UEngineSound()
{

}

void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	UEngineSound* NewSound = new UEngineSound();
}