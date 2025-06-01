// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Ih_UISubsystem.generated.h"

class UIh_ActivatableBase;
class UIh_PrimaryLayout;
struct FGameplayTag;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

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

private:
	UPROPERTY(Transient)
	TObjectPtr<UIh_PrimaryLayout> CratedPrimaryLayout;
};
