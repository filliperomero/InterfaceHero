// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsDataRegistry.h"

#include "Ih_FunctionLibrary.h"
#include "Ih_GameplayTags.h"
#include "Settings/Ih_GameUserSettings.h"
#include "Widgets/Options/Ih_OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Scalar.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_String.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringBool.h"

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

	TArray<UIh_ListDataObject_Base*> AllChildListItems;
	
	for (UIh_ListDataObject_Base* ChildListItem : FoundTabCollection->GetAllChildListData())
	{
		if (!IsValid(ChildListItem)) continue;
	
		AllChildListItems.Add(ChildListItem);
	
		if (ChildListItem->HasAnyChildListData())
		{
			FindChildListDataRecursively(ChildListItem, AllChildListItems);
		}
	}

	return AllChildListItems;
}

void UIh_OptionsDataRegistry::FindChildListDataRecursively(UIh_ListDataObject_Base* InParentData, TArray<UIh_ListDataObject_Base*>& OutChildListData) const
{
	if (!IsValid(InParentData) || !InParentData->HasAnyChildListData()) return;
	
	for (UIh_ListDataObject_Base* SubChildListItem : InParentData->GetAllChildListData())
	{
		if (!IsValid(SubChildListItem)) continue;

		OutChildListData.Add(SubChildListItem);

		if (SubChildListItem->HasAnyChildListData())
		{
			FindChildListDataRecursively(SubChildListItem, OutChildListData);
		}
	}
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
		UIh_ListDataObject_String* TestItem = NewObject<UIh_ListDataObject_String>();
		TestItem->SetDataID(FName("TestItem"));
		TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Image Item")));
		TestItem->SetSoftDescriptionImage(UIh_FunctionLibrary::GetOptionsSoftImageByTag(InterfaceHeroGameplayTags::Image_TestImage));
		TestItem->SetDescriptionRichText(FText::FromString(TEXT("The image to display can be specified in the project settings. It can be anything the developer assigned in there")));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UIh_OptionsDataRegistry::InitAudioCollectionTab()
{
	UIh_ListDataObject_Collection* AudioTabCollection = NewObject<UIh_ListDataObject_Collection>();
	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

	// Volume Category
	{
		UIh_ListDataObject_Collection* VolumeCategoryCollection = NewObject<UIh_ListDataObject_Collection>();
		VolumeCategoryCollection->SetDataID(FName("VolumeCategoryCollection"));
		VolumeCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Volume")));

		AudioTabCollection->AddChildListData(VolumeCategoryCollection);

		// Overall Volume
		{
			UIh_ListDataObject_Scalar* OverallVolume = NewObject<UIh_ListDataObject_Scalar>();
			OverallVolume->SetDataID(FName("OverallVolume"));
			OverallVolume->SetDataDisplayName(FText::FromString(TEXT("Overall Volume")));
			OverallVolume->SetDescriptionRichText(FText::FromString(TEXT("Adjusts the master volume level for all game audio, including music, sound effects, and dialogue.")));
			OverallVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			OverallVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			OverallVolume->SetSliderStepSize(0.01f);
			OverallVolume->SetDefaultValueFromString(LexToString(1.f));
			OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			OverallVolume->SetNumberFormattingOptions(UIh_ListDataObject_Scalar::NoDecimal());

			OverallVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallVolume));
			OverallVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallVolume));

			OverallVolume->SetShouldApplyChangeImmediately(true);

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}

		// Music Volume
		{
			UIh_ListDataObject_Scalar* MusicVolume = NewObject<UIh_ListDataObject_Scalar>();
			MusicVolume->SetDataID(FName("MusicVolume"));
			MusicVolume->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));
			MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("Adjusts the volume level of the background music without affecting sound effects or dialogue.")));
			MusicVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			MusicVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			MusicVolume->SetSliderStepSize(0.01f);
			MusicVolume->SetDefaultValueFromString(LexToString(1.f));
			MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			MusicVolume->SetNumberFormattingOptions(UIh_ListDataObject_Scalar::NoDecimal());

			MusicVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMusicVolume));
			MusicVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMusicVolume));

			MusicVolume->SetShouldApplyChangeImmediately(true);

			VolumeCategoryCollection->AddChildListData(MusicVolume);
		}

		// Sound FX Volume
		{
			UIh_ListDataObject_Scalar* SoundFXVolume = NewObject<UIh_ListDataObject_Scalar>();
			SoundFXVolume->SetDataID(FName("SoundFXVolume"));
			SoundFXVolume->SetDataDisplayName(FText::FromString(TEXT("Sound FX Volume")));
			SoundFXVolume->SetDescriptionRichText(FText::FromString(TEXT("Adjusts the volume level of sound effects, such as footsteps, attacks, item pickups, and environment sounds.")));
			SoundFXVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			SoundFXVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			SoundFXVolume->SetSliderStepSize(0.01f);
			SoundFXVolume->SetDefaultValueFromString(LexToString(1.f));
			SoundFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			SoundFXVolume->SetNumberFormattingOptions(UIh_ListDataObject_Scalar::NoDecimal());

			SoundFXVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetSoundFXVolume));
			SoundFXVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetSoundFXVolume));

			SoundFXVolume->SetShouldApplyChangeImmediately(true);

			VolumeCategoryCollection->AddChildListData(SoundFXVolume);
		}
	}

	// Sound Category
	{
		UIh_ListDataObject_Collection* SoundCategoryCollection = NewObject<UIh_ListDataObject_Collection>();
		SoundCategoryCollection->SetDataID(FName("SoundCategoryCollection"));
		SoundCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Sound")));

		AudioTabCollection->AddChildListData(SoundCategoryCollection);

		// Allow Background Audio
		{
			UIh_ListDataObject_StringBool* AllowBackgroundAudio = NewObject<UIh_ListDataObject_StringBool>();
			AllowBackgroundAudio->SetDataID(FName("AllowBackgroundAudio"));
			AllowBackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("Allow Background Audio")));
			AllowBackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
			AllowBackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
			AllowBackgroundAudio->SetDescriptionRichText(FText::FromString(TEXT("Allow Background Audio.")));
			AllowBackgroundAudio->SetFalseAsDefaultValue();

			AllowBackgroundAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAllowBackgroundAudio));
			AllowBackgroundAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAllowBackgroundAudio));

			AllowBackgroundAudio->SetShouldApplyChangeImmediately(true);

			SoundCategoryCollection->AddChildListData(AllowBackgroundAudio);
		}
	}

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
