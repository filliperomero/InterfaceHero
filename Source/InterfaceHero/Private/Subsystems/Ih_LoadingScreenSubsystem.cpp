// Copyright Fillipe Romero. All Rights Reserved.

#include "Subsystems/Ih_LoadingScreenSubsystem.h"
#include "PreLoadScreenManager.h"
#include "Blueprint/UserWidget.h"
#include "Settings/Ih_LoadingScreenSettings.h"

bool UIh_LoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

void UIh_LoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &ThisClass::OnMapPreLoaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnMapPostLoaded);
}

void UIh_LoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

UWorld* UIh_LoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	if (const UGameInstance* OwningGameInstance = GetGameInstance())
	{
		return OwningGameInstance->GetWorld();
	}

	return nullptr;
}

void UIh_LoadingScreenSubsystem::Tick(float DeltaTime)
{
	TryUpdateLoadingScreen();
}

ETickableTickType UIh_LoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return ETickableTickType::Never;
	}

	return ETickableTickType::Conditional;
}

bool UIh_LoadingScreenSubsystem::IsTickable() const
{
	return GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

TStatId UIh_LoadingScreenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UIh_LoadingScreenSubsystem, STATGROUP_Tickables);
}

void UIh_LoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance != GetGameInstance()) return;

	SetTickableTickType(ETickableTickType::Conditional);
	
	bIsCurrentlyLoadingMap = true;

	TryUpdateLoadingScreen();
}

void UIh_LoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	if (IsValid(LoadedWorld) && LoadedWorld->GetGameInstance() == GetGameInstance())
	{
		bIsCurrentlyLoadingMap = false;
	}
}

bool UIh_LoadingScreenSubsystem::IsPreLoadScreenActive() const
{
	if (const FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
	{
		return PreLoadScreenManager->HasValidActivePreLoadScreen();
	}
	
	return false;
}

bool UIh_LoadingScreenSubsystem::CheckTheNeedToShowLoadingScreen()
{
	if (bIsCurrentlyLoadingMap)
	{
		CurrentLoadingReason = TEXT("Loading Level");
		return true;
	}

	UWorld* OwningWorld = GetGameInstance()->GetWorld();

	if (!IsValid(OwningWorld))
	{
		CurrentLoadingReason = TEXT("Initializing World");
		return true;
	}

	if (!OwningWorld->HasBegunPlay())
	{
		CurrentLoadingReason = TEXT("World hasn't begun play yet");
		return true;
	}

	if (!OwningWorld->GetFirstPlayerController())
	{
		CurrentLoadingReason = TEXT("Player Controller is not valid yet");
		return true;
	}

	if (!OwningWorld->GetFirstPlayerController())
	{
		CurrentLoadingReason = TEXT("Player Controller is not valid yet");
		return true;
	}

	// Check if the game states, player states, or player character, actor component are ready.
	
	return false;
}

bool UIh_LoadingScreenSubsystem::ShouldShowLoadingScreen()
{
	const UIh_LoadingScreenSettings* LoadingScreenSettings = GetDefault<UIh_LoadingScreenSettings>();

	if (GIsEditor && !LoadingScreenSettings->bShowLoadingScreenInEditor) return false;

	if (CheckTheNeedToShowLoadingScreen())
	{
		GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = true;

		return true;
	}

	CurrentLoadingReason = TEXT("Waiting for Texture Streaming");

	// There's no need to show the loading screen. Allow the world to be rendered to our viewport.
	GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = false;

	const float CurrentTimeInSeconds = FPlatformTime::Seconds();

	if (HoldLoadingScreenStartUpTime < 0.f)
	{
		HoldLoadingScreenStartUpTime = CurrentTimeInSeconds;
	}

	const float ElapsedTime = CurrentTimeInSeconds - HoldLoadingScreenStartUpTime;

	if (ElapsedTime < LoadingScreenSettings->HoldLoadingScreenExtraSeconds)
	{
		return true;
	}
	
	return false;
}

void UIh_LoadingScreenSubsystem::TryDisplayLoadingScreenIfNone()
{
	if (CachedCreatedLoadingScreenWidget.IsValid()) return;
	
	const UIh_LoadingScreenSettings* LoadingScreenSettings = GetDefault<UIh_LoadingScreenSettings>();
	
	TSubclassOf<UUserWidget> LoadedWidgetClass = LoadingScreenSettings->GetLoadingScreenWidgetClassChecked();

	// We cannot rely on Player Controller or World because we're doing this under level transition
	UUserWidget* CreatedWidget = UUserWidget::CreateWidgetInstance(*GetGameInstance(), LoadedWidgetClass, NAME_None);

	check(CreatedWidget);
	
	CachedCreatedLoadingScreenWidget = CreatedWidget->TakeWidget();

	GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(CachedCreatedLoadingScreenWidget.ToSharedRef(), 1000);
}

void UIh_LoadingScreenSubsystem::TryUpdateLoadingScreen()
{
	// Check if there's any startUp loading screen that's currently active
	if (IsPreLoadScreenActive()) return;
	
	if (ShouldShowLoadingScreen())
	{
		TryDisplayLoadingScreenIfNone();
		OnLoadingReasonUpdated.Broadcast(CurrentLoadingReason);
	}
	else
	{
		SetTickableTickType(ETickableTickType::Never);
	}
}
