// Copyright Fillipe Romero. All Rights Reserved.

#include "Subsystems/Ih_UISubsystem.h"
#include "Ih_FunctionLibrary.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Ih_ActivatableBase.h"
#include "Widgets/Ih_ConfirmScreen.h"
#include "Widgets/Ih_PrimaryLayout.h"
#include "Ih_GameplayTags.h"

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

void UIh_UISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UIh_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UIh_ActivatableBase*)> AsyncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, InSoftWidgetClass, InWidgetStackTag, AsyncPushStateCallback]()
		{
			UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

			check(LoadedWidgetClass && CratedPrimaryLayout)

			UCommonActivatableWidgetContainerBase* FoundWidgetStack = CratedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);

			UIh_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UIh_ActivatableBase>(
				LoadedWidgetClass,
				[&](UIh_ActivatableBase& CreatedWidgetInstance)
				{
					AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
				});

			AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
		})
	);
}

void UIh_UISubsystem::PushConfirmScreenToModalStackAsync(EIh_ConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMessage, TFunction<void(EIh_ConfirmScreenButtonType)> ButtonClickedCallback)
{
	UIh_ConfirmScreenInfoObject* CreatedInfoObject = nullptr;
	
	switch (InScreenType)
	{
	case EIh_ConfirmScreenType::Ok:
		CreatedInfoObject = UIh_ConfirmScreenInfoObject::CreateOkScreen(InScreenTitle, InScreenMessage);
		break;
	case EIh_ConfirmScreenType::YesNo:
		CreatedInfoObject = UIh_ConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMessage);
		break;
	case EIh_ConfirmScreenType::OkCancel:
		CreatedInfoObject = UIh_ConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMessage);
		break;
	default:
		break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(
		InterfaceHeroGameplayTags::WidgetStack_Modal,
		UIh_FunctionLibrary::GetSoftWidgetClassByTag(InterfaceHeroGameplayTags::Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UIh_ActivatableBase* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UIh_ConfirmScreen* CreatedConfirmScreen = CastChecked<UIh_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
	);
}
