// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_Value.h"

void UIh_ListDataObject_Value::SetDataDynamicGetter(const TSharedPtr<FIh_OptionsDataInteractionHelper>& InDynamicGetter)
{
	DataDynamicGetter = InDynamicGetter;
}

void UIh_ListDataObject_Value::SetDataDynamicSetter(const TSharedPtr<FIh_OptionsDataInteractionHelper>& InDynamicSetter)
{
	DataDynamicSetter = InDynamicSetter;
}
