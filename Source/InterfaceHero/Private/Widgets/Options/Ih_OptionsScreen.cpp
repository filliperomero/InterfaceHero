// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "Ih_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"

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

void UIh_OptionsScreen::OnResetBoundActionTrigger()
{
	Debug::Print(TEXT("Reset Bound Action Triggered"));
}

void UIh_OptionsScreen::OnBackBoundActionTrigger()
{
	DeactivateWidget();
}
