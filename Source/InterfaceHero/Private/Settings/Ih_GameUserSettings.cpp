// Copyright Fillipe Romero. All Rights Reserved.

#include "Settings/Ih_GameUserSettings.h"

// Values cannot be initialized in the header file when it's a Config property
UIh_GameUserSettings::UIh_GameUserSettings()
	: OverallVolume(1.f), MusicVolume(1.f), SoundFXVolume(1.f), bAllowBackgroundAudio(false), bUseHDRAudioMode(false)
{
}

UIh_GameUserSettings* UIh_GameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UIh_GameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}

void UIh_GameUserSettings::SetOverallVolume(float InOverallVolume)
{
	OverallVolume = InOverallVolume;

	// The actual logic for controlling the volume goes here
}

void UIh_GameUserSettings::SetMusicVolume(float InMusicVolume)
{
	MusicVolume = InMusicVolume;
}

void UIh_GameUserSettings::SetSoundFXVolume(float InSoundFXVolume)
{
	SoundFXVolume = InSoundFXVolume;
}

void UIh_GameUserSettings::SetAllowBackgroundAudio(bool bIsAllowed)
{
	bAllowBackgroundAudio = bIsAllowed;
}

void UIh_GameUserSettings::SetUseHDRAudioMode(bool bUseHDR)
{
	bUseHDRAudioMode = bUseHDR;
}

float UIh_GameUserSettings::GetCurrentDisplayGamma()
{
	if (GEngine)
	{
		return GEngine->GetDisplayGamma();
	}

	return 0.f;
}

void UIh_GameUserSettings::SetCurrentDisplayGamma(float InNewGamma)
{
	if (GEngine)
	{
		GEngine->DisplayGamma = InNewGamma;
	}
}
