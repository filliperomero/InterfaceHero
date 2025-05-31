// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IH_PlayerController.generated.h"

UCLASS()
class INTERFACEHERO_API AIH_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;	
};
