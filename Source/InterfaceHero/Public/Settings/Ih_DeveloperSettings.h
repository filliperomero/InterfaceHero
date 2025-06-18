// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "Ih_DeveloperSettings.generated.h"

class UIh_ActivatableBase;

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Interface Hero Settings"))
class INTERFACEHERO_API UIh_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta=(ForceInlineRow, Categories="Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UIh_ActivatableBase>> WidgetMap;

	UPROPERTY(Config, EditAnywhere, Category = "Options Image Reference", meta=(ForceInlineRow, Categories="Image"))
	TMap<FGameplayTag, TSoftObjectPtr<UTexture2D>> OptionsScreenSoftImageMap;
};
