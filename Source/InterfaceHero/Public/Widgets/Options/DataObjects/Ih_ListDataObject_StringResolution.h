// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListDataObject_String.h"
#include "Ih_ListDataObject_StringResolution.generated.h"

UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_StringResolution : public UIh_ListDataObject_String
{
	GENERATED_BODY()

public:
	void InitResolutionValues();

protected:
	virtual void OnDataObjectInitialized() override;

private:
	static FString ResolutionToValueString(const FIntPoint& InResolution);
	static FText ResolutionToDisplayText(const FIntPoint& InResolution);

	FString MaximumAllowedResolution;
};
