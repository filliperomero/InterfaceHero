// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListDataObject_String.h"
#include "Ih_ListDataObject_StringBool.generated.h"

UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_StringBool : public UIh_ListDataObject_String
{
	GENERATED_BODY()

public:
	void OverrideTrueDisplayText(const FText& InNewTrueDisplayText);
	void OverrideFalseDisplayText(const FText& InNewFalseDisplayText);
	void SetTrueAsDefaultValue();
	void SetFalseAsDefaultValue();

protected:
	virtual void OnDataObjectInitialized() override;

private:
	void TryInitBoolValues();
	
	const FString TrueString { TEXT("true") };
	const FString FalseString { TEXT("false") };
};
