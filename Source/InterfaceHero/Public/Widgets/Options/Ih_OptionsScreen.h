// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Ih_ActivatableBase.h"
#include "Ih_OptionsScreen.generated.h"

class UIh_OptionsDetailsView;
class UIh_TabListWidgetBase;
class UIh_OptionsDataRegistry;
class UIh_CommonListView;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_OptionsScreen : public UIh_ActivatableBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

private:
	UIh_OptionsDataRegistry* GetOrCreateDataRegistry();
	
	void OnResetBoundActionTrigger();
	void OnBackBoundActionTrigger();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

	void OnListViewItemHovered(UObject* InHoveredItem, bool bIsHovered);
	void OnListViewItemSelected(UObject* InSelectedItem);
	FString TryGetEntryWidgetClassName(UObject* InOwningListItem) const;

	/** Bound Widgets */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UIh_TabListWidgetBase> TabListWidget_OptionsTabs;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UIh_CommonListView> CommonListView_OptionsList;
	
	UPROPERTY(meta = (BindWidget))
    TObjectPtr<UIh_OptionsDetailsView> DetailsView_ListEntryInfo;
	/** Bound Widgets */

	// Handle the creation of data in the option's screen. Direct access to this variable is forbidden
	UPROPERTY(Transient)
	TObjectPtr<UIh_OptionsDataRegistry> OwningDataRegistry;
	
	UPROPERTY(EditDefaultsOnly, Category="Options Screen", meta=(RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
