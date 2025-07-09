// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_KeyRemap.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "Ih_DebugHelper.h"

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

FSlateBrush UIh_ListDataObject_KeyRemap::GetIconFromCurrentKey() const
{
	check(OwningInputUserSettings)
	
	FSlateBrush OutBrush;
	UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(OwningInputUserSettings->GetLocalPlayer());

	check(CommonInputSubsystem)
	
	const bool bHasFoundBrush = UCommonInputPlatformSettings::Get()->TryGetInputBrush(OutBrush, GetOwningKeyMapping()->GetCurrentKey(), DesiredInputKeyType, CommonInputSubsystem->GetCurrentGamepadName());

	if (!bHasFoundBrush)
	{
		Debug::Print(TEXT("Unable to find an icon for the key ") + GetOwningKeyMapping()->GetCurrentKey().GetDisplayName().ToString() + TEXT(" Empty brush was applied."));
	}
	
	return OutBrush;
}

void UIh_ListDataObject_KeyRemap::BindNewInputKey(const FKey& InNewKey)
{
	check(OwningInputUserSettings);

	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = OwningMappingName;
	KeyArgs.Slot = OwningMappableKeySlot;
	KeyArgs.NewKey = InNewKey;

	FGameplayTagContainer Container;

	OwningInputUserSettings->MapPlayerKey(KeyArgs, Container);
	OwningInputUserSettings->SaveSettings();

	NotifyListDataModified(this, EIh_OptionsListDataModifyReason::DirectlyModified);
}

bool UIh_ListDataObject_KeyRemap::HasDefaultValue() const
{
	return GetOwningKeyMapping()->GetDefaultKey().IsValid();
}

bool UIh_ListDataObject_KeyRemap::CanResetBackToDefaultValue() const
{
	return HasDefaultValue() && GetOwningKeyMapping()->IsCustomized();
}

bool UIh_ListDataObject_KeyRemap::TryResetBackToDefaultValue()
{
	if (CanResetBackToDefaultValue())
	{
		check(OwningInputUserSettings);
		
		GetOwningKeyMapping()->ResetToDefault();
		OwningInputUserSettings->SaveSettings();
		
		NotifyListDataModified(this, EIh_OptionsListDataModifyReason::ResetToDefault);

		return true;
	}

	return false;
}

FPlayerKeyMapping* UIh_ListDataObject_KeyRemap::GetOwningKeyMapping() const
{
	check(OwningKeyProfile)

	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = OwningMappingName;
	KeyArgs.Slot = OwningMappableKeySlot;
	
	return OwningKeyProfile->FindKeyMapping(KeyArgs);
}
