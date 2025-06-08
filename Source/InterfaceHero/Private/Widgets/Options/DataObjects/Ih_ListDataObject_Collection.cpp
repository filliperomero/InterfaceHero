// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_Collection.h"

void UIh_ListDataObject_Collection::AddChildListData(UIh_ListDataObject_Base* InChildListData)
{
	InChildListData->InitDataObject();
	InChildListData->SetParentData(this);
	
	ChildListDataArray.Add(InChildListData);
}

TArray<UIh_ListDataObject_Base*> UIh_ListDataObject_Collection::GetAllChildListData() const
{
	return ChildListDataArray;
}

bool UIh_ListDataObject_Collection::HasAnyChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}
