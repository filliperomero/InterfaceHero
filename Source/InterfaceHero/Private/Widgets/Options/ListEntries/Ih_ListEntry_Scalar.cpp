// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_Scalar.h"

void UIh_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UIh_ListEntry_Scalar::OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);
}

void UIh_ListEntry_Scalar::OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
}
