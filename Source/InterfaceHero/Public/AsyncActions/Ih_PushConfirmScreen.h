// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types/Ih_EnumTypes.h"
#include "Ih_PushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, EIh_ConfirmScreenButtonType, ClickedButtonType);

UCLASS()
class INTERFACEHERO_API UIh_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext="WorldContextObject", HidePin="WorldContextObject", BlueprintInternalUseOnly="true", DisplayName="Show Confirmation Screen"))
	static UIh_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		EIh_ConfirmScreenType ScreenType,
		FText InScreenTitle,
		FText InScreenMessage
	);

	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnButtonClicked;

private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	EIh_ConfirmScreenType CachedScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;
};
