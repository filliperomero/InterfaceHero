// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Types/Ih_EnumTypes.h"
#include "Ih_ListEntry_Base.generated.h"

class UIh_ListDataObject_Base;
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bIsHovered, bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bIsHovered);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	/** The Child Class should override this function to handle the initialization needed. Super call is expected. */
	virtual void OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject);

	/** The Child Class should override this function to update the UI values after the data object has been modified. Super call is not needed. */
	virtual void OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason);

private:
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional, AllowPrivateAccess="true"))
	TObjectPtr<UCommonTextBlock> CommonText_SettingDisplayName; 
	/** Bound Widgets */
};
