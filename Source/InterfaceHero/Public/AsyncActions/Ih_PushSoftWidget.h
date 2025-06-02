// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Ih_PushSoftWidget.generated.h"

class UIh_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UIh_ActivatableBase*, PushedWidget);

UCLASS()
class INTERFACEHERO_API UIh_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", HidePin="WorldContextObject", BlueprintInternalUseOnly="true", DisplayName="Push Soft Widget To Widget Stack"))
	static UIh_PushSoftWidget* PushSoftWidget(
		const UObject* WorldContextObject,
		APlayerController* OwningPlayerController,
		TSoftClassPtr<UIh_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta=(Categories="WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	TWeakObjectPtr<APlayerController> CachedOwningPlayerController;
	TSoftClassPtr<UIh_ActivatableBase> CachedSoftWidgetClass;
	FGameplayTag CachedWidgetStackTag;
	bool bCachedFocusOnNewlyPushedWidget { false };
};
