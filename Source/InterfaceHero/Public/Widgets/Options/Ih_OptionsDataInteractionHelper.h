// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UIh_GameUserSettings;

class INTERFACEHERO_API FIh_OptionsDataInteractionHelper
{
public:
	FIh_OptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath);

	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);
	
private:
	FCachedPropertyPath CachedDynamicFunctionPath;
	TWeakObjectPtr<UIh_GameUserSettings> CachedWeakGameUserSettings;
};
