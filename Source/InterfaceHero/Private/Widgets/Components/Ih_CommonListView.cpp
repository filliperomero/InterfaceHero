// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Components/Ih_CommonListView.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Options/Ih_DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Base.h"
#include "Widgets/Options/ListEntries/Ih_ListEntry_Base.h"

UUserWidget& UIh_CommonListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime()) return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);

	TSubclassOf<UIh_ListEntry_Base> WidgetClass = DataListEntryMapping->FindEntryWidgetClassByDataObject(CastChecked<UIh_ListDataObject_Base>(Item));

	return GenerateTypedEntry<UIh_ListEntry_Base>(WidgetClass, OwnerTable);
}

#if WITH_EDITOR
void UIh_CommonListView::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable DataListEntryMapping has no valid data asset assigned ") +
			GetClass()->GetName()
			+ TEXT(" needs a valid data asset to function properly")
			));
	}
}
#endif

