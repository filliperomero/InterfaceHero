// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"

void UIh_ListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UIh_ListDataObject_Base::OnDataObjectInitialized()
{
}

void UIh_ListDataObject_Base::NotifyListDataModified(UIh_ListDataObject_Base* ModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);
}
