// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Ih_GameUserSettings.generated.h"

UCLASS()
class INTERFACEHERO_API UIh_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UIh_GameUserSettings();
	
	static UIh_GameUserSettings* Get();

	/** Gameplay Collection Tab */
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }

	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InDifficulty) { CurrentGameDifficulty = InDifficulty; }

	/** Audio Collection Tab */
	UFUNCTION()
	float GetOverallVolume() const { return OverallVolume; }

	UFUNCTION()
	void SetOverallVolume(float InOverallVolume);

private:
	/** Gameplay Collection Tab */
	UPROPERTY(Config)
	FString CurrentGameDifficulty;

	/** Audio Collection Tab */
	UPROPERTY(Config)
	float OverallVolume;
};
