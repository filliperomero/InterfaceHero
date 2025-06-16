// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsDetailsView.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"

void UIh_OptionsDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClearDetailsViewInfo();
}

void UIh_OptionsDetailsView::UpdateDetailsViewInfo(UIh_ListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName)
{
	if (!IsValid(InDataObject)) return;

	CommonTextBlock_Title->SetText(InDataObject->GetDataDisplayName());

	if (!InDataObject->GetSoftDescriptionImage().IsNull())
	{
		CommonLazyImage_DescriptionImage->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	CommonRichText_Description->SetText(InDataObject->GetDescriptionRichText());

	const FString DynamicDetails = FString::Printf(
		TEXT("Data Object Class: <Bold>%s</>\n\nEntry Widget Class: <Bold>%s</>"),
		*InDataObject->GetClass()->GetName(),
		*InEntryWidgetClassName
	);
	
	CommonRichText_DynamicDetails->SetText(FText::FromString(DynamicDetails));
	CommonRichText_DisabledReason->SetText(InDataObject->GetDisabledRichText());
}

void UIh_OptionsDetailsView::ClearDetailsViewInfo()
{
	CommonTextBlock_Title->SetText(FText::GetEmpty());
	CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichText_Description->SetText(FText::GetEmpty());
	CommonRichText_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichText_DisabledReason->SetText(FText::GetEmpty());
}
