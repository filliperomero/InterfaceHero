// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsDataRegistry.h"

#include "Settings/Ih_GameUserSettings.h"
#include "Widgets/Options/Ih_OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_String.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
	MakeShared<FIh_OptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UIh_GameUserSettings,SetterOrGetterFuncName))

void UIh_OptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

TArray<UIh_ListDataObject_Base*> UIh_OptionsDataRegistry::GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const
{
	UIh_ListDataObject_Collection* const* FoundTabCollectionPtr = RegisteredOptionsTabCollections.FindByPredicate(
		[InSelectedTabID](UIh_ListDataObject_Collection* AvailableTabCollection)->bool
		{
			return AvailableTabCollection->GetDataID() == InSelectedTabID;
		}
	);

	checkf(FoundTabCollectionPtr, TEXT("No valid tab found under the ID %s"), *InSelectedTabID.ToString())

	const UIh_ListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;

	return FoundTabCollection->GetAllChildListData();
}

void UIh_OptionsDataRegistry::InitGameplayCollectionTab()
{
	UIh_ListDataObject_Collection* GameplayTabCollection = NewObject<UIh_ListDataObject_Collection>();
	GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));

	// This is the full code for constructor data interactor helper
	// TSharedPtr<FIh_OptionsDataInteractionHelper> ConstructedHelper = MakeShared<FIh_OptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UIh_GameUserSettings, GetCurrentGameDifficulty));

	// Game Difficulty
	{
		UIh_ListDataObject_String* GameDifficulty = NewObject<UIh_ListDataObject_String>();
		GameDifficulty->SetDataID(FName("GameDifficulty"));
		GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Difficulty")));
		GameDifficulty->SetDescriptionRichText(FText::FromString(
			TEXT("Adjusts the difficulty of the game experience.\n\n<Bold>Easy:</> Focuses on the story experience. "
			"Provides the most relaxing combat.\n\n<Bold>Normal:</> Offers slightly harder combat experience.\n\n<Bold>Hard:</> "
			"Offers a much more challenging combat experience.\n\n<Bold>Very Hard:</> Provides the most challenging combat "
			"experience. Not recommended for first play through.")));
		GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("Easy")));
		GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
		GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("Hard")));
		GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("Very Hard")));
		GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));

		GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentGameDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentGameDifficulty));

		GameDifficulty->SetShouldApplyChangeImmediately(true);

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	// Test Item
	{
		UIh_ListDataObject_String* TesteItem = NewObject<UIh_ListDataObject_String>();
		TesteItem->SetDataID(FName("TesteItem"));
		TesteItem->SetDataDisplayName(FText::FromString(TEXT("Teste Item")));

		GameplayTabCollection->AddChildListData(TesteItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UIh_OptionsDataRegistry::InitAudioCollectionTab()
{
	UIh_ListDataObject_Collection* AudioTabCollection = NewObject<UIh_ListDataObject_Collection>();
	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UIh_OptionsDataRegistry::InitVideoCollectionTab()
{
	UIh_ListDataObject_Collection* VideoTabCollection = NewObject<UIh_ListDataObject_Collection>();
	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UIh_OptionsDataRegistry::InitControlCollectionTab()
{
	UIh_ListDataObject_Collection* ControlTabCollection = NewObject<UIh_ListDataObject_Collection>();
	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}
