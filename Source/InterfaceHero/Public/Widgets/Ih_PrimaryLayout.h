// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Ih_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class INTERFACEHERO_API UIh_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InStackTag) const;

protected:
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta=(Categories="WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InWidgetStack);

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
