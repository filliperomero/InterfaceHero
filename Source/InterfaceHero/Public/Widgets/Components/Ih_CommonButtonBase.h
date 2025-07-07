// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Ih_CommonButtonBase.generated.h"

class UCommonLazyImage;
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_CommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

	UFUNCTION()
	FText GetButtonDisplayText() const;

	UFUNCTION(BlueprintCallable)
	void SetButtonDisplayImage(const FSlateBrush& InBrush);

private:
	virtual void NativePreConstruct() override;
	
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	
	/** Bound Widgets */
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess="true"))
	TObjectPtr<UCommonLazyImage> CommonLazyImage_ButtonImage;
	/** Bound Widgets */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IH Button", meta=(AllowPrivateAccess="true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IH Button", meta=(AllowPrivateAccess="true"))
	bool bUseUpperCaseForButtonText { false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IH Button", meta=(AllowPrivateAccess="true"))
	FText ButtonDescriptionText;
};
