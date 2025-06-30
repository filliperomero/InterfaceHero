// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"

#include "Settings/Ih_GameUserSettings.h"

void UIh_ListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UIh_ListDataObject_Base::AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition)
{
	EditConditionDescArray.Add(InEditCondition);
}

void UIh_ListDataObject_Base::AddEditDependencyData(UIh_ListDataObject_Base* InDependencyData)
{
	if (!InDependencyData->OnListDataModified.IsBoundToObject(this))
	{
		InDependencyData->OnListDataModified.AddUObject(this, &ThisClass::OnEditDependencyDataModified);
	}
}

bool UIh_ListDataObject_Base::IsDataCurrentlyEditable()
{
	bool bIsEditable = true;

	if (EditConditionDescArray.IsEmpty()) return bIsEditable;

	FString DisabledRichReason;

	for (const FOptionsDataEditConditionDescriptor& Condition : EditConditionDescArray)
	{
		if (!Condition.IsValid() || Condition.IsEditConditionMet()) continue;

		bIsEditable = false;

		DisabledRichReason.Append(Condition.GetDisabledRichReason());

		SetDisabledRichText(FText::FromString(DisabledRichReason));

		if (Condition.HasForcedStringValue())
		{
			const FString ForcedStringValue = Condition.GetDisabledForcedStringValue();

			// Check if the current value this data object has can be set to the forced value
			if (CanSetToForcedStringValue(ForcedStringValue))
			{
				OnSetToForcedStringValue(ForcedStringValue);
			}
		}
	}

	return bIsEditable;
}

void UIh_ListDataObject_Base::OnDataObjectInitialized()
{
}

void UIh_ListDataObject_Base::NotifyListDataModified(UIh_ListDataObject_Base* ModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);

	if (bShouldApplyChangeImmediately)
	{
		UIh_GameUserSettings::Get()->ApplySettings(true);
	}
}

void UIh_ListDataObject_Base::OnEditDependencyDataModified(UIh_ListDataObject_Base* ModifiedDependencyData, EIh_OptionsListDataModifyReason ModifyReason)
{
	OnDependencyDataModified.Broadcast(ModifiedDependencyData, ModifyReason);
}
