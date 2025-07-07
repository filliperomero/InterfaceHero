// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Ih_ListDataObject_Base.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Ih_ListDataObject_KeyRemap.generated.h"

class UEnhancedPlayerMappableKeyProfile;
class UEnhancedInputUserSettings;

UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_KeyRemap : public UIh_ListDataObject_Base
{
	GENERATED_BODY()

public:
	void InitKeyRemapData(UEnhancedInputUserSettings* InOwningInputUserSettings, UEnhancedPlayerMappableKeyProfile* InOwningKeyProfile, ECommonInputType InDesiredInputKeyType, const FPlayerKeyMapping& InOwningPlayerKeyMapping);
	FSlateBrush GetIconFromCurrentKey() const;

private:
	FPlayerKeyMapping* GetOwningKeyMapping() const;
	
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputUserSettings> OwningInputUserSettings;

	UPROPERTY(Transient)
	TObjectPtr<UEnhancedPlayerMappableKeyProfile> OwningKeyProfile;

	ECommonInputType DesiredInputKeyType;
	FName OwningMappingName;
	EPlayerMappableKeySlot OwningMappableKeySlot;
};
