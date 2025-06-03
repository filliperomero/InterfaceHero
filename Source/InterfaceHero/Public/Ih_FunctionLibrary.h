// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Ih_FunctionLibrary.generated.h"

class UIh_ActivatableBase;
/**
 * 
 */
UCLASS()
class INTERFACEHERO_API UIh_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Interface Hero Function Library")
	static TSoftClassPtr<UIh_ActivatableBase> GetSoftWidgetClassByTag(UPARAM(meta=(Categories="Widget")) FGameplayTag InWidgetTag);
};
