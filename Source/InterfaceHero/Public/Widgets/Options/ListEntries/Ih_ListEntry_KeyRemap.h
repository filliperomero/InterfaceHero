// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListEntry_Base.h"
#include "Ih_ListEntry_KeyRemap.generated.h"

class UIh_ListDataObject_KeyRemap;
class UIh_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ListEntry_KeyRemap : public UIh_ListEntry_Base
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason) override;

private:
	void OnRemapKeyButtonClicked();
	void OnResetKeyBindingButtonClicked();
	
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonButtonBase> CommonButton_RemapKey;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonButtonBase> CommonButton_ResetKeyBinding;
	/** Bound Widgets */

	UPROPERTY(Transient)
	TObjectPtr<UIh_ListDataObject_KeyRemap> CachedOwningKeyRemapDataObject;
};
