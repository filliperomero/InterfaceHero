// Copyright Fillipe Romero. All Rights Reserved.

#include "InterfaceHero/Public/Player/Ih_PlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/Ih_GameUserSettings.h"

void AIh_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> OutCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), OutCameras);

	if (!OutCameras.IsEmpty())
	{
		SetViewTarget(OutCameras[0]);
	}

	UIh_GameUserSettings* GameUserSettings = UIh_GameUserSettings::Get();

	if (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult() == -1.f)
	{
		GameUserSettings->RunHardwareBenchmark();
		GameUserSettings->ApplyHardwareBenchmarkResults();
	}
}
