// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Ih_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"

UIh_ConfirmScreenInfoObject* UIh_ConfirmScreenInfoObject::CreateOkScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UIh_ConfirmScreenInfoObject* InfoObject = NewObject<UIh_ConfirmScreenInfoObject>();

	InfoObject->ScreenMessage = InScreenMessage;
	InfoObject->ScreenTitle = InScreenTitle;

	FIh_ConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EIh_ConfirmScreenButtonType::Closed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

	return InfoObject;
}

UIh_ConfirmScreenInfoObject* UIh_ConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UIh_ConfirmScreenInfoObject* InfoObject = NewObject<UIh_ConfirmScreenInfoObject>();

	InfoObject->ScreenMessage = InScreenMessage;
	InfoObject->ScreenTitle = InScreenTitle;

	FIh_ConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EIh_ConfirmScreenButtonType::Confirmed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

	FIh_ConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EIh_ConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

	InfoObject->AvailableScreenButtons.Add(YesButtonInfo);
	InfoObject->AvailableScreenButtons.Add(NoButtonInfo);

	return InfoObject;
}

UIh_ConfirmScreenInfoObject* UIh_ConfirmScreenInfoObject::CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UIh_ConfirmScreenInfoObject* InfoObject = NewObject<UIh_ConfirmScreenInfoObject>();

	InfoObject->ScreenMessage = InScreenMessage;
	InfoObject->ScreenTitle = InScreenTitle;

	FIh_ConfirmScreenButtonInfo OkButtonInfo;
	OkButtonInfo.ConfirmScreenButtonType = EIh_ConfirmScreenButtonType::Confirmed;
	OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));

	FIh_ConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EIh_ConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

	InfoObject->AvailableScreenButtons.Add(OkButtonInfo);
	InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return InfoObject;
}

void UIh_ConfirmScreen::InitConfirmScreen(UIh_ConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EIh_ConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

	// Check if the entry box has old buttons created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/**
		 * Clear all old buttons that the entry box has. The widget type for the entry box
		 * is specified in the child Widget Blueprint
		 */
		DynamicEntryBox_Buttons->Reset<UIh_CommonButtonBase>(
			[](UIh_CommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty())

	for (FIh_ConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		UIh_CommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UIh_CommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback, AvailableButtonInfo, this]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);

				DeactivateWidget();
			}
		);
	}

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		// Set Focus on the last Button. So if we have 2 buttons and the last one is No/Cancel, our gamepad will focus on this button so we don't accidentally press the wrong button
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
