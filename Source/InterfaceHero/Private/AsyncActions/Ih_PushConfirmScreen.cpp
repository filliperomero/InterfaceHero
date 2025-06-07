// Copyright Fillipe Romero. All Rights Reserved.

#include "AsyncActions/Ih_PushConfirmScreen.h"

#include "Subsystems/Ih_UISubsystem.h"

void UIh_PushConfirmScreen::Activate()
{
	Super::Activate();

	UIh_UISubsystem* Subsystem = UIh_UISubsystem::Get(CachedOwningWorld.Get());
	
	Subsystem->PushConfirmScreenToModalStackAsync(
		CachedScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this](EIh_ConfirmScreenButtonType ClickedButtonType)
		{
			OnButtonClicked.Broadcast(ClickedButtonType);

			SetReadyToDestroy();
		}
	);
}

UIh_PushConfirmScreen* UIh_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, EIh_ConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UIh_PushConfirmScreen* Node = NewObject<UIh_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;
			
			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
