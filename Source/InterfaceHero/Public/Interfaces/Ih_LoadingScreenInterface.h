// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ih_LoadingScreenInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UIh_LoadingScreenInterface : public UInterface
{
	GENERATED_BODY()
};

class INTERFACEHERO_API IIh_LoadingScreenInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Loading Screen")
	void OnLoadingScreenActivated();

	UFUNCTION(BlueprintNativeEvent, Category = "Loading Screen")
	void OnLoadingScreenDeactivated();
};
