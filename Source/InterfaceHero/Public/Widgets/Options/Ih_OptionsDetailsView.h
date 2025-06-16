// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ih_OptionsDetailsView.generated.h"

class UIh_ListDataObject_Base;
class UCommonRichTextBlock;
class UCommonLazyImage;
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_OptionsDetailsView : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateDetailsViewInfo(UIh_ListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName = FString());
	void ClearDetailsViewInfo();

protected:
	virtual void NativeOnInitialized() override;

private:
	/** Bound Widgets */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonLazyImage> CommonLazyImage_DescriptionImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_Description;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_DynamicDetails;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_DisabledReason;
	/** Bound Widgets */
};
