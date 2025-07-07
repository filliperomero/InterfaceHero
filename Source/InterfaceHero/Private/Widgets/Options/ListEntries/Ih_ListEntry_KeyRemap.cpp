// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_KeyRemap.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_KeyRemap.h"

void UIh_ListEntry_KeyRemap::OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningKeyRemapDataObject = CastChecked<UIh_ListDataObject_KeyRemap>(InOwningListDataObject);

	CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UIh_ListEntry_KeyRemap::OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
	if (IsValid(CachedOwningKeyRemapDataObject))
	{
		CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
	}
}
