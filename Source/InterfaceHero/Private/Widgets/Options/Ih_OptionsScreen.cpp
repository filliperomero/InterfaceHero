// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsScreen.h"
#include "ICommonInputModule.h"
#include "Ih_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "Settings/Ih_GameUserSettings.h"
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

void UIh_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
	TArray<UIh_ListDataObject_Base*> ListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);

	CommonListView_OptionsList->SetListItems(ListSourceItems);
	CommonListView_OptionsList->RequestRefresh();

	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);
		CommonListView_OptionsList->SetSelectedIndex(0);
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
		CommonListView_ListEntryInfo->UpdateDetailsViewInfo(CastChecked<UIh_ListDataObject_Base>(InHoveredItem), TryGetEntryWidgetClassName(InHoveredItem));
	}
	else
	{
		if (UIh_ListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UIh_ListDataObject_Base>())
		{
			CommonListView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
		}
	}
}

void UIh_OptionsScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!IsValid(InSelectedItem)) return;

	CommonListView_ListEntryInfo->UpdateDetailsViewInfo(CastChecked<UIh_ListDataObject_Base>(InSelectedItem), TryGetEntryWidgetClassName(InSelectedItem));
}

FString UIh_OptionsScreen::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
	if (UUserWidget* EntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
	{
		return EntryWidget->GetClass()->GetName();
	}

	return TEXT("Entry Widget not valid");
}
