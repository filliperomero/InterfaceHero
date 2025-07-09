// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_KeyRemap.h"

#include "Ih_FunctionLibrary.h"
#include "Ih_GameplayTags.h"
#include "Subsystems/Ih_UISubsystem.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"
#include "Widgets/Options/Ih_KeyRemapScreen.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_KeyRemap.h"

void UIh_ListEntry_KeyRemap::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_RemapKey->OnClicked().AddUObject(this, &ThisClass::OnRemapKeyButtonClicked);
	CommonButton_ResetKeyBinding->OnClicked().AddUObject(this, &ThisClass::OnResetKeyBindingButtonClicked);
}

void UIh_ListEntry_KeyRemap::OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningKeyRemapDataObject = CastChecked<UIh_ListDataObject_KeyRemap>(InOwningListDataObject);

	CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UIh_ListEntry_KeyRemap::OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
	if (IsValid(CachedOwningKeyRemapDataObject))
	{
		CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
	}
}

void UIh_ListEntry_KeyRemap::OnRemapKeyButtonClicked()
{
	UIh_UISubsystem::Get(this)->PushSoftWidgetToStackAsync(
		InterfaceHeroGameplayTags::WidgetStack_Modal,
		UIh_FunctionLibrary::GetSoftWidgetClassByTag(InterfaceHeroGameplayTags::Widget_KeyRemapScreen),
		[this](EAsyncPushWidgetState PushState, UIh_ActivatableBase* PushedWidget)
		{
			if (PushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UIh_KeyRemapScreen* KeyRemapScreen = CastChecked<UIh_KeyRemapScreen>(PushedWidget);
				KeyRemapScreen->OnKeyRemapScreenKeyPressed.BindUObject(this, &ThisClass::OnKeyToRemapPressed);
				KeyRemapScreen->OnKeyRemapScreenKeySelectCanceled.BindUObject(this, &ThisClass::OnKeyRemapCanceled);
				
				if (IsValid(CachedOwningKeyRemapDataObject))
				{
					KeyRemapScreen->SetDesiredInputTypeToFilter(CachedOwningKeyRemapDataObject->GetDesiredInputKeyType());
				}
			}
		}
	);
}

void UIh_ListEntry_KeyRemap::OnResetKeyBindingButtonClicked()
{
}

void UIh_ListEntry_KeyRemap::OnKeyToRemapPressed(const FKey& PressedKey)
{
	if (IsValid(CachedOwningKeyRemapDataObject))
	{
		CachedOwningKeyRemapDataObject->BindNewInputKey(PressedKey);
	}
}

void UIh_ListEntry_KeyRemap::OnKeyRemapCanceled(const FString& CanceledReason)
{
	UIh_UISubsystem::Get(this)->PushConfirmScreenToModalStackAsync(
		EIh_ConfirmScreenType::Ok,
		FText::FromString(TEXT("Key Remap")),
		FText::FromString(CanceledReason),
		[](EIh_ConfirmScreenButtonType ClickedButton){}
	);
}
