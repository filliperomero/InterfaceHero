// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_KeyRemap.h"

void UIh_ListDataObject_KeyRemap::InitKeyRemapData(UEnhancedInputUserSettings* InOwningInputUserSettings,
	UEnhancedPlayerMappableKeyProfile* InOwningKeyProfile, ECommonInputType InDesiredInputKeyType,
	const FPlayerKeyMapping& InOwningPlayerKeyMapping)
{
	OwningInputUserSettings = InOwningInputUserSettings;
	OwningKeyProfile = InOwningKeyProfile;
	DesiredInputKeyType = InDesiredInputKeyType;
	OwningMappingName = InOwningPlayerKeyMapping.GetMappingName();
	OwningMappableKeySlot = InOwningPlayerKeyMapping.GetSlot();
}
