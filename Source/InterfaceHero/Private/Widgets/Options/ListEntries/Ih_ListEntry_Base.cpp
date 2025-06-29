// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_Base.h"

#include "CommonInputSubsystem.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"

void UIh_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bIsHovered)
{
	BP_OnListEntryWidgetHovered(bIsHovered, IsListItemSelected());
}

void UIh_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	OnOwningListDataObjectSet(CastChecked<UIh_ListDataObject_Base>(ListItemObject));
}

FReply UIh_ListEntry_Base::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	if (IsValid(CommonInputSubsystem) && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (UWidget* WidgetToFocus = BP_GetWidgetToFocusForGamepad())
		{
			if (TSharedPtr<SWidget> SlateWidgetToFocus = WidgetToFocus->GetCachedWidget())
			{
				return FReply::Handled().SetUserFocus(SlateWidgetToFocus.ToSharedRef());
			}
		}
	}

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UIh_ListEntry_Base::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	// Manually reset our widget highlight state back to default after it is released. This is to fix an issue when changing tabs with keyboard and all entries are highlighted
	NativeOnListEntryWidgetHovered(false);
}

void UIh_ListEntry_Base::OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
	}

	// This check is necessary because everytime we switch back to the tab showing this entry, this function will be called, and we don't want to keep bounding
	if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}

	OnToggleEditableState(InOwningListDataObject->IsDataCurrentlyEditable());
}

void UIh_ListEntry_Base::OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
}

void UIh_ListEntry_Base::OnToggleEditableState(const bool bIsEditable)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetIsEnabled(bIsEditable);
	}
}

void UIh_ListEntry_Base::SelectThisEntryWidget()
{
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
