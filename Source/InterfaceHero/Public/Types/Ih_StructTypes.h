// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "Ih_StructTypes.generated.h"

USTRUCT()
struct FOptionsDataEditConditionDescriptor
{
	GENERATED_BODY()

public:
	void SetEditConditionFunc(const TFunction<bool()>& InEditConditionFunc) { EditConditionFunc = InEditConditionFunc; }
	bool IsValid() const { return EditConditionFunc != nullptr; }
	bool IsEditConditionMet() const
	{
		if (IsValid())
		{
			return EditConditionFunc();
		}
		
		return true;
	}
	
	FString GetDisabledRichReason() const { return DisabledRichReason; }
	void SetDisabledRichReason(const FString& InDisabledRichReason) { DisabledRichReason = InDisabledRichReason; }

	bool HasForcedStringValue() const { return DisabledForcedStringValue.IsSet(); }
	FString GetDisabledForcedStringValue() const { return DisabledForcedStringValue.GetValue(); }
	void SetForcedStringValue(const FString& InDisabledForcedStringValue) { DisabledForcedStringValue = InDisabledForcedStringValue; }
	
private:
	TFunction<bool()> EditConditionFunc;
	FString DisabledRichReason;
	TOptional<FString> DisabledForcedStringValue;
};