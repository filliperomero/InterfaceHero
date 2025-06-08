// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsScreen.h"
#include "ICommonInputModule.h"
#include "Ih_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/Components/Ih_TabListWidgetBase.h"
#include "Widgets/Options/Ih_OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Collection.h"

void UIh_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTrigger)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTrigger)
		)
	);
}

void UIh_OptionsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (UIh_ListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection) continue;

		const FName TabID = TabCollection->GetDataID();
		// This means we already created it
		if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID) != nullptr) continue;

		TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

UIh_OptionsDataRegistry* UIh_OptionsScreen::GetOrCreateDataRegistry()
{
	if (!OwningDataRegistry)
	{
		OwningDataRegistry = NewObject<UIh_OptionsDataRegistry>();
		OwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}

	checkf(OwningDataRegistry, TEXT("Data registry for options screen is not valid"));

	return OwningDataRegistry;
}

void UIh_OptionsScreen::OnResetBoundActionTrigger()
{
	Debug::Print(TEXT("Reset Bound Action Triggered"));
}

void UIh_OptionsScreen::OnBackBoundActionTrigger()
{
	DeactivateWidget();
}
