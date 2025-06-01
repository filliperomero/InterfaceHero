// Copyright Fillipe Romero. All Rights Reserved.

#include "Subsystems/Ih_UISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Ih_ActivatableBase.h"
#include "Widgets/Ih_PrimaryLayout.h"

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
		FStreamableDelegate::CreateLambda([&]()
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
