// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"

TSubclassOf<UIh_ListEntry_Base> UIh_DataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject(UIh_ListDataObject_Base* InDataObject) const
{
	check(InDataObject);

	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
	{
		if (TSubclassOf<UIh_ListDataObject_Base> ConvertedDataObjectClass = TSubclassOf<UIh_ListDataObject_Base>(DataObjectClass))
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}

	return TSubclassOf<UIh_ListEntry_Base>();
}
