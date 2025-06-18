// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsScreen.h"
#include "ICommonInputModule.h"
#include "Ih_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "Settings/Ih_GameUserSettings.h"
#include "Subsystems/Ih_UISubsystem.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"
#include "Widgets/Components/Ih_CommonListView.h"
#include "Widgets/Components/Ih_TabListWidgetBase.h"
#include "Widgets/Options/Ih_OptionsDataRegistry.h"
#include "Widgets/Options/Ih_OptionsDetailsView.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Collection.h"
#include "Widgets/Options/ListEntries/Ih_ListEntry_Base.h"

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

	TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);

	CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
	CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
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

void UIh_OptionsScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	// Trigger a save on all values we have inside the class to the file
	UIh_GameUserSettings::Get()->ApplySettings(true);
}

UWidget* UIh_OptionsScreen::NativeGetDesiredFocusTarget() const
{
	// Logic to regain focus when we are, for example, showing a confirmation screen and go back to the options screen (gamepad-only problem where it was not getting focus back).
	if (UObject* SelectedObject = CommonListView_OptionsList->GetSelectedItem())
	{
		if (UUserWidget* SelectedEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(SelectedObject))
		{
			return SelectedEntryWidget;
		}
	}
	
	return Super::NativeGetDesiredFocusTarget();
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
	if (ResettableDataArray.IsEmpty()) return;

	UCommonButtonBase* SelectedTabButton = TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabListWidget_OptionsTabs->GetActiveTab());

	const FString TabButtonName = CastChecked<UIh_CommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();

	UIh_UISubsystem::Get(this)->PushConfirmScreenToModalStackAsync(
		EIh_ConfirmScreenType::YesNo,
		FText::FromString(TEXT("Reset")),
		FText::FromString(TEXT("Are you sure you want to reset all the settings under the ") + TabButtonName + TEXT(" tab.")),
		[this](EIh_ConfirmScreenButtonType ClickedButtonType)
		{
			if (ClickedButtonType != EIh_ConfirmScreenButtonType::Confirmed) return;

			// Flag to indicate we're resetting data. So when our delegate triggers OnListViewListDataModified, we can make sure we aren't modifying ResettableDataArray
			bIsResettingData = true;
			bool bHasDataFailedToReset = false;

			for (UIh_ListDataObject_Base* DataToReset : ResettableDataArray)
			{
				if (!IsValid(DataToReset)) continue;

				if (DataToReset->TryResetBackToDefaultValue())
				{
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" was reset"));
				}
				else
				{
					bHasDataFailedToReset = true;
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" was not reset"));
				}
			}

			if (!bHasDataFailedToReset)
			{
				ResettableDataArray.Empty();
				RemoveActionBinding(ResetActionHandle);
			}

			bIsResettingData = false;
		}
	);
}

void UIh_OptionsScreen::OnBackBoundActionTrigger()
{
	DeactivateWidget();
}

void UIh_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
	DetailsView_ListEntryInfo->ClearDetailsViewInfo();
	
	TArray<UIh_ListDataObject_Base*> ListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);

	CommonListView_OptionsList->SetListItems(ListSourceItems);
	CommonListView_OptionsList->RequestRefresh();

	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);
		CommonListView_OptionsList->SetSelectedIndex(0);
	}

	ResettableDataArray.Empty();

	for (UIh_ListDataObject_Base* ListSourceItem : ListSourceItems)
	{
		if (!IsValid(ListSourceItem)) return;

		if (!ListSourceItem->OnListDataModified.IsBoundToObject(this))
		{
			ListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);
		}

		if (ListSourceItem->CanResetBackToDefaultValue())
		{
			ResettableDataArray.AddUnique(ListSourceItem);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
	else
	{
		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
}

void UIh_OptionsScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bIsHovered)
{
	if (!IsValid(InHoveredItem)) return;

	UIh_ListEntry_Base* HoveredEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem<UIh_ListEntry_Base>(InHoveredItem);

	check(HoveredEntryWidget)

	HoveredEntryWidget->NativeOnListEntryWidgetHovered(bIsHovered);

	if (bIsHovered)
	{
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(CastChecked<UIh_ListDataObject_Base>(InHoveredItem), TryGetEntryWidgetClassName(InHoveredItem));
	}
	else
	{
		if (UIh_ListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UIh_ListDataObject_Base>())
		{
			DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
		}
	}
}

void UIh_OptionsScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!IsValid(InSelectedItem)) return;

	DetailsView_ListEntryInfo->UpdateDetailsViewInfo(CastChecked<UIh_ListDataObject_Base>(InSelectedItem), TryGetEntryWidgetClassName(InSelectedItem));
}

FString UIh_OptionsScreen::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
	if (UUserWidget* EntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
	{
		return EntryWidget->GetClass()->GetName();
	}

	return TEXT("Entry Widget not valid");
}

void UIh_OptionsScreen::OnListViewListDataModified(UIh_ListDataObject_Base* ModifiedData, EIh_OptionsListDataModifyReason ModifyReason)
{
	if (!IsValid(ModifiedData) || bIsResettingData) return;

	if (ModifiedData->CanResetBackToDefaultValue())
	{
		ResettableDataArray.AddUnique(ModifiedData);

		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
	else
	{
		if (ResettableDataArray.Contains(ModifiedData))
		{
			ResettableDataArray.Remove(ModifiedData);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
}
