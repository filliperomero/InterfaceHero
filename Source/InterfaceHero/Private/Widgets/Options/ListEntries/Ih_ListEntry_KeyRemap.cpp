// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/ListEntries/Ih_ListEntry_KeyRemap.h"

#include "Ih_FunctionLibrary.h"
#include "Ih_GameplayTags.h"
#include "Subsystems/Ih_UISubsystem.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"
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
		[](EAsyncPushWidgetState PushState, UIh_ActivatableBase* PushedWidget)
		{
			
		}
	);
}

void UIh_ListEntry_KeyRemap::OnResetKeyBindingButtonClicked()
{
}
