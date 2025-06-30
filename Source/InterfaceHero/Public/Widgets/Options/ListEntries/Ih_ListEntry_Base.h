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
	/** The Child WBP should override this function for the gamepad interaction to function properly */
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnEntryReleased() override;

	/** The Child Class should override this function to handle the initialization needed. Super call is expected. */
	virtual void OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject);

	/** The Child Class should override this function to update the UI values after the data object has been modified. Super call is not needed. */
	virtual void OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason);

	/** The Child Class should override this function to update the UI values after the dependency data object has been modified. Super call is not needed. */
	virtual void OnOwningDependencyListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedDependencyData, EIh_OptionsListDataModifyReason ModifyReason);

	/** Child class should override this function to change the editable state of the widgets it owns. Super call is expected. */
	virtual void OnToggleEditableState(bool bIsEditable); 

	void SelectThisEntryWidget();

private:
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional, AllowPrivateAccess="true"))
	TObjectPtr<UCommonTextBlock> CommonText_SettingDisplayName; 
	/** Bound Widgets */

	UPROPERTY(Transient)
	TObjectPtr<UIh_ListDataObject_Base> CachedOwningDataObject;
};
