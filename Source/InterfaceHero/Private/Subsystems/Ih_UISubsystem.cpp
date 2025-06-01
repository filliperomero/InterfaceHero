// Copyright Fillipe Romero. All Rights Reserved.

#include "Subsystems/Ih_UISubsystem.h"

UIh_UISubsystem* UIh_UISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UIh_UISubsystem>(World->GetGameInstance());
	}

	return nullptr;
}

bool UIh_UISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> OutClasses;
		GetDerivedClasses(GetClass(), OutClasses);

		return OutClasses.IsEmpty();
	}

	return false;
}

void UIh_UISubsystem::RegisterCreatedPrimaryLayoutWidget(UIh_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	
	CratedPrimaryLayout = InCreatedWidget;
}
