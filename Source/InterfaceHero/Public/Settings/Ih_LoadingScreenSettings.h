// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Ih_LoadingScreenSettings.generated.h"

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Interface Hero Loading Screen Settings"))
class INTERFACEHERO_API UIh_LoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	TSubclassOf<UUserWidget> GetLoadingScreenWidgetClassChecked() const;
	
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	TSoftClassPtr<UUserWidget> SoftLoadingScreenWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	float HoldLoadingScreenExtraSeconds { 3.f };

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	bool bShowLoadingScreenInEditor { false };
};
