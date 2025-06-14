// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListDataObject_Base.h"
#include "Ih_ListDataObject_Value.generated.h"

class FIh_OptionsDataInteractionHelper;

UCLASS(Abstract)
class INTERFACEHERO_API UIh_ListDataObject_Value : public UIh_ListDataObject_Base
{
	GENERATED_BODY()

public:
	void SetDataDynamicGetter(const TSharedPtr<FIh_OptionsDataInteractionHelper>& InDynamicGetter);
	void SetDataDynamicSetter(const TSharedPtr<FIh_OptionsDataInteractionHelper>& InDynamicSetter);

protected:
	// We use a smart pointer here to not have a possible memory leak, since we cannot use unreal to handle that for us (using UPROPERTY)
	TSharedPtr<FIh_OptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FIh_OptionsDataInteractionHelper> DataDynamicSetter;
};
