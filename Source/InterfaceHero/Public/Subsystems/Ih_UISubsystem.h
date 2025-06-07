// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/Ih_EnumTypes.h"
#include "Ih_UISubsystem.generated.h"

class UIh_ActivatableBase;
class UIh_PrimaryLayout;
struct FGameplayTag;
class UIh_CommonButtonBase;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UIh_CommonButtonBase*, BroadcastingButton, FText, DescriptionText);

UCLASS()
class INTERFACEHERO_API UIh_UISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UIh_UISubsystem* Get(const UObject* WorldContextObject);
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UIh_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UIh_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UIh_ActivatableBase*)> AsyncPushStateCallback);
	void PushConfirmScreenToModalStackAsync(EIh_ConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMessage, TFunction<void(EIh_ConfirmScreenButtonType)> ButtonClickedCallback);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:
	UPROPERTY(Transient)
	TObjectPtr<UIh_PrimaryLayout> CratedPrimaryLayout;
};
