// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Ih_ActivatableBase.h"
#include "Ih_OptionsScreen.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_OptionsScreen : public UIh_ActivatableBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnResetBoundActionTrigger();
	void OnBackBoundActionTrigger();
	
	UPROPERTY(EditDefaultsOnly, Category="Options Screen", meta=(RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
