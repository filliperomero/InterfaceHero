// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListDataObject_String.h"
#include "Ih_ListDataObject_StringInteger.generated.h"

UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_StringInteger : public UIh_ListDataObject_String
{
	GENERATED_BODY()

public:
	void AddIntegerOption(const int32 InIntegerValue, const FText& InDisplayText);

	virtual void OnEditDependencyDataModified(UIh_ListDataObject_Base* ModifiedDependencyData, EIh_OptionsListDataModifyReason ModifyReason = EIh_OptionsListDataModifyReason::DirectlyModified) override;

protected:
	virtual void OnDataObjectInitialized() override;
};
