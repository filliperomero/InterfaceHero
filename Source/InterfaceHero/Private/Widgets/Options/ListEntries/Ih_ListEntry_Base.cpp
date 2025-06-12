// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_Base.h"

#include "CommonTextBlock.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"

void UIh_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OnOwningListDataObjectSet(CastChecked<UIh_ListDataObject_Base>(ListItemObject));
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
}

void UIh_ListEntry_Base::OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
}
