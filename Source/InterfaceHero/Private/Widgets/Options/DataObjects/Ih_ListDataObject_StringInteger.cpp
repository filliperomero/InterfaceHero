// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringInteger.h"
#include "Widgets/Options/Ih_OptionsDataInteractionHelper.h"

void UIh_ListDataObject_StringInteger::AddIntegerOption(const int32 InIntegerValue, const FText& InDisplayText)
{
	AddDynamicOption(LexToString(InIntegerValue), InDisplayText);
}

void UIh_ListDataObject_StringInteger::OnEditDependencyDataModified(UIh_ListDataObject_Base* ModifiedDependencyData, EIh_OptionsListDataModifyReason ModifyReason)
{
	if (DataDynamicGetter)
	{
		CurrentStringValue = DataDynamicGetter->GetValueAsString();

		if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
		{
			CurrentDisplayText = FText::FromString(TEXT("Custom"));
		}

		NotifyListDataModified(this, EIh_OptionsListDataModifyReason::DependencyModified);
	}

	Super::OnEditDependencyDataModified(ModifiedDependencyData, ModifyReason);
}

void UIh_ListDataObject_StringInteger::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Custom"));
	}
}
