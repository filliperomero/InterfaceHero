// Copyright Fillipe Romero. All Rights Reserved.

#include "Settings/Ih_GameUserSettings.h"

UIh_GameUserSettings* UIh_GameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UIh_GameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}
