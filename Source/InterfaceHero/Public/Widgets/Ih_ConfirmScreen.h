// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types/Ih_EnumTypes.h"
#include "Widgets/Ih_ActivatableBase.h"
#include "Ih_ConfirmScreen.generated.h"

class UDynamicEntryBox;
class UCommonTextBlock;

USTRUCT(BlueprintType)
struct FIh_ConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIh_ConfirmScreenButtonType ConfirmScreenButtonType { EIh_ConfirmScreenButtonType::Unknown };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

UCLASS()
class INTERFACEHERO_API UIh_ConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	static UIh_ConfirmScreenInfoObject* CreateOkScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	static UIh_ConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	static UIh_ConfirmScreenInfoObject* CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	
	UPROPERTY(Transient)
	FText ScreenTitle { FText::GetEmpty() };

	UPROPERTY(Transient)
	FText ScreenMessage { FText::GetEmpty() };

	UPROPERTY(Transient)
	TArray<FIh_ConfirmScreenButtonInfo> AvailableScreenButtons;
};

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ConfirmScreen : public UIh_ActivatableBase
{
	GENERATED_BODY()

public:
	void InitConfirmScreen(UIh_ConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EIh_ConfirmScreenButtonType)> ClickedButtonCallback);

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Buttons;
};
