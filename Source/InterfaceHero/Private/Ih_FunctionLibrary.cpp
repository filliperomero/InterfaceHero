// Copyright Fillipe Romero. All Rights Reserved.

#include "Ih_FunctionLibrary.h"
#include "Settings/Ih_DeveloperSettings.h"

TSoftClassPtr<UIh_ActivatableBase> UIh_FunctionLibrary::GetSoftWidgetClassByTag(UPARAM(meta=(Categories="Widget")) FGameplayTag InWidgetTag)
{
	const UIh_DeveloperSettings* DeveloperSettings = GetDefault<UIh_DeveloperSettings>();

	checkf(DeveloperSettings->WidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString())

	return DeveloperSettings->WidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UIh_FunctionLibrary::GetOptionsSoftImageByTag(FGameplayTag InImageTag)
{
	const UIh_DeveloperSettings* DeveloperSettings = GetDefault<UIh_DeveloperSettings>();

	checkf(DeveloperSettings->OptionsScreenSoftImageMap.Contains(InImageTag), TEXT("Could not find the corresponding image under the tag %s"), *InImageTag.ToString())

	return DeveloperSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}
