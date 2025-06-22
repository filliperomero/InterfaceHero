// Copyright Fillipe Romero. All Rights Reserved.

#include "Settings/Ih_GameUserSettings.h"

// Values cannot be initialized in the header file when it's a Config property
UIh_GameUserSettings::UIh_GameUserSettings()
	: OverallVolume(1.f)
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
