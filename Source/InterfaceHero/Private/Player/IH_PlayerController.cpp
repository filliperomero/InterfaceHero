// Copyright Fillipe Romero. All Rights Reserved.

#include "InterfaceHero/Public/Player/IH_PlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AIH_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> OutCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), OutCameras);

	if (!OutCameras.IsEmpty())
	{
		SetViewTarget(OutCameras[0]);
	}
}
