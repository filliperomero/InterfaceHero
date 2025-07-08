// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Widgets/Ih_ActivatableBase.h"
#include "Ih_KeyRemapScreen.generated.h"

class UCommonRichTextBlock;
class FKeyRemapScreenInputPreprocessor;

DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeyPressedDelegate, const FKey&/*PressedKey*/);
DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeySelectCanceledDelegate, const FString&/*CanceledReason*/);

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_KeyRemapScreen : public UIh_ActivatableBase
{
	GENERATED_BODY()

public:
	void SetDesiredInputTypeToFilter(const ECommonInputType InDesiredInputType);

	FOnKeyRemapScreenKeyPressedDelegate OnKeyRemapScreenKeyPressed;
	FOnKeyRemapScreenKeySelectCanceledDelegate OnKeyRemapScreenKeySelectCanceled;

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

private:
	void OnValidKeyPressedDetected(const FKey& PressedKey);
	void OnKeySelectedCanceled (const FString& CanceledReason);

	/* Delay a tick to make sure the input key is captured properly before calling the PreDeactivateCallback and deactivating the widget*/
	void RequestDeactivateWidget(TFunction<void()> PreDeactivateCallback);
	
	/** Bound Widgets */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_RemapMessage;
	/** Bound Widgets */

	TSharedPtr<FKeyRemapScreenInputPreprocessor> InputPreprocessor;
	ECommonInputType DesiredInputType;
};
