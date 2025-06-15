// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_String.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"
#include "Widgets/Components/Ih_CommonRotator.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_String.h"

void UIh_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_PreviousOption->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
	CommonButton_NextOption->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);

	CommonRotator_AvailableOptions->OnClicked().AddLambda([this](){SelectThisEntryWidget();});
}

void UIh_ListEntry_String::OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningStringDataObject = CastChecked<UIh_ListDataObject_String>(InOwningListDataObject);

	CommonRotator_AvailableOptions->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionsTextArray());
	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UIh_ListEntry_String::OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
	if (!IsValid(CachedOwningStringDataObject)) return;

	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UIh_ListEntry_String::OnPreviousOptionButtonClicked()
{
	if (IsValid(CachedOwningStringDataObject))
	{
		CachedOwningStringDataObject->BackToPreviousOption();
	}

	SelectThisEntryWidget();
}

void UIh_ListEntry_String::OnNextOptionButtonClicked()
{
	if (IsValid(CachedOwningStringDataObject))
	{
		CachedOwningStringDataObject->AdvanceToNextOption();
	}

	SelectThisEntryWidget();
}
