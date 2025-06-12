// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_String.h"

void UIh_ListDataObject_String::AddDynamicOption(const FString& InStringValue, const FText& InDisplayText)
{
	AvailableOptionsStringArray.Add(InStringValue);
	AvailableOptionsTextArray.Add(InDisplayText);
}

void UIh_ListDataObject_String::AdvanceToNextOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	const int32 CurrentIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextIndex = CurrentIndex + 1;

	if (AvailableOptionsStringArray.IsValidIndex(NextIndex))
	{
		CurrentStringValue = AvailableOptionsStringArray[NextIndex];
	}
	else
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	TrySetDisplayTextFromStringValue(CurrentStringValue);
	
	NotifyListDataModified(this);
}

void UIh_ListDataObject_String::BackToPreviousOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	const int32 CurrentIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 PreviousIndex = CurrentIndex - 1;

	if (AvailableOptionsStringArray.IsValidIndex(PreviousIndex))
	{
		CurrentStringValue = AvailableOptionsStringArray[PreviousIndex];
	}
	else
	{
		CurrentStringValue = AvailableOptionsStringArray.Last();
	}

	TrySetDisplayTextFromStringValue(CurrentStringValue);
	
	NotifyListDataModified(this);
}

void UIh_ListDataObject_String::OnDataObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		// TODO: Read from the saved string value and use it to set the CurrentStringValue
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
	}
}

bool UIh_ListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InStringValue)
{
	const int32 CurrentIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);

	if (AvailableOptionsTextArray.IsValidIndex(CurrentIndex))
	{
		CurrentDisplayText = AvailableOptionsTextArray[CurrentIndex];
		return true;
	}

	return false;
}
