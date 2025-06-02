// Copyright Fillipe Romero. All Rights Reserved.


#include "AsyncActions/Ih_PushSoftWidget.h"

#include "Subsystems/Ih_UISubsystem.h"
#include "Widgets/Ih_ActivatableBase.h"

void UIh_PushSoftWidget::Activate()
{
	Super::Activate();

	UIh_UISubsystem* Subsystem = UIh_UISubsystem::Get(CachedOwningWorld.Get());

	Subsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass, [this](EAsyncPushWidgetState InPushState, UIh_ActivatableBase* PushedWidget)
	{
		switch (InPushState)
		{
		case EAsyncPushWidgetState::OnCreatedBeforePush:
			
			PushedWidget->SetOwningPlayer(CachedOwningPlayerController.Get());
			OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
			
			break;
		case EAsyncPushWidgetState::AfterPush:

			AfterPush.Broadcast(PushedWidget);

			if (bCachedFocusOnNewlyPushedWidget)
			{
				if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
				{
					WidgetToFocus->SetFocus();
				}
			}

			SetReadyToDestroy();
			
			break;
		}
	});
}

UIh_PushSoftWidget* UIh_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, TSoftClassPtr<UIh_ActivatableBase> InSoftWidgetClass, UPARAM(meta=(Categories="WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"))

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UIh_PushSoftWidget* Node = NewObject<UIh_PushSoftWidget>();
			Node->CachedOwningWorld = World;
			Node->CachedOwningPlayerController = OwningPlayerController;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
			
			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
