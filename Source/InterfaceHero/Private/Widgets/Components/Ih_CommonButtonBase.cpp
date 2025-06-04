// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Components/Ih_CommonButtonBase.h"

#include "CommonTextBlock.h"

void UIh_CommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}

void UIh_CommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UIh_CommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText)
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}
