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
#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringEnum.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringInteger.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringResolution.h"
#include "Internationalization/StringTableRegistry.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
	MakeShared<FIh_OptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UIh_GameUserSettings,SetterOrGetterFuncName))

#define GET_DESCRIPTION(InKey) LOCTABLE("/Game/Blueprints/StringTables/ST_OptionsScreenDescription.ST_OptionsScreenDescription", InKey)

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

		// Use HDR Audio
		{
			UIh_ListDataObject_StringBool* UseHDRAudioMode = NewObject<UIh_ListDataObject_StringBool>();
			UseHDRAudioMode->SetDataID(FName("useHDRAudioMode"));
			UseHDRAudioMode->SetDataDisplayName(FText::FromString(TEXT("Use HDR Audio Mode")));
			UseHDRAudioMode->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
			UseHDRAudioMode->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
			UseHDRAudioMode->SetDescriptionRichText(FText::FromString(TEXT("Use HDR Mode")));
			UseHDRAudioMode->SetFalseAsDefaultValue();
			UseHDRAudioMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetUseHDRAudioMode));
			UseHDRAudioMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetUseHDRAudioMode));
			UseHDRAudioMode->SetShouldApplyChangeImmediately(true);

			SoundCategoryCollection->AddChildListData(UseHDRAudioMode);
		}
	}

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UIh_OptionsDataRegistry::InitVideoCollectionTab()
{
	UIh_ListDataObject_Collection* VideoTabCollection = NewObject<UIh_ListDataObject_Collection>();
	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	UIh_ListDataObject_StringEnum* CreatedWindowMode = nullptr;

	// Display Category
	{
		UIh_ListDataObject_Collection* DisplayCategoryCollection = NewObject<UIh_ListDataObject_Collection>();
		DisplayCategoryCollection->SetDataID(FName("DisplayCategoryCollection"));
		DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));

		VideoTabCollection->AddChildListData(DisplayCategoryCollection);

		FOptionsDataEditConditionDescriptor PackagedBuildOnlyCondition;
		PackagedBuildOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This Setting can only be adjusted in a packaged build.</>"));
		PackagedBuildOnlyCondition.SetEditConditionFunc(
			[]()->bool
			{
				const bool bIsInEditor = GIsEditor || GIsPlayInEditorWorld;
				
				return !bIsInEditor;
			}
		);

		// Window Mode
		{
			UIh_ListDataObject_StringEnum* WindowMode = NewObject<UIh_ListDataObject_StringEnum>();
			WindowMode->SetDataID(FName("WindowMode"));
			WindowMode->SetDataDisplayName(FText::FromString(TEXT("Window Mode")));
			WindowMode->SetDescriptionRichText(GET_DESCRIPTION("WindowModeDescKey"));
			WindowMode->AddEnumOption(EWindowMode::Fullscreen, FText::FromString(TEXT("Fullscreen")));
			WindowMode->AddEnumOption(EWindowMode::Windowed, FText::FromString(TEXT("Windowed")));
			WindowMode->AddEnumOption(EWindowMode::WindowedFullscreen, FText::FromString(TEXT("Borderless Windowed")));
			WindowMode->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
			
			WindowMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFullscreenMode));
			WindowMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFullscreenMode));

			WindowMode->SetShouldApplyChangeImmediately(true);

			WindowMode->AddEditCondition(PackagedBuildOnlyCondition);

			DisplayCategoryCollection->AddChildListData(WindowMode);

			CreatedWindowMode = WindowMode;
		}

		// Screen Resolution
		{
			UIh_ListDataObject_StringResolution* ScreenResolution = NewObject<UIh_ListDataObject_StringResolution>();
			ScreenResolution->SetDataID(FName("ScreenResolution"));
			ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Screen Resolution")));
			ScreenResolution->SetDescriptionRichText(GET_DESCRIPTION("ScreenResolutionsDescKey"));
			ScreenResolution->InitResolutionValues();

			ScreenResolution->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetScreenResolution));
			ScreenResolution->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetScreenResolution));

			ScreenResolution->SetShouldApplyChangeImmediately(true);

			ScreenResolution->AddEditCondition(PackagedBuildOnlyCondition);

			FOptionsDataEditConditionDescriptor WindowModeEditCondition;
			WindowModeEditCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>Screen Resolution is not adjustable when the 'Window Mode' is set to Borderless Window. The value must match with the maximum allowed resolution.</>"));
			WindowModeEditCondition.SetForcedStringValue(ScreenResolution->GetMaximumAllowedResolution());
			WindowModeEditCondition.SetEditConditionFunc(
				[CreatedWindowMode]()->bool
				{
					return CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() != EWindowMode::WindowedFullscreen;
				}
			);

			ScreenResolution->AddEditCondition(WindowModeEditCondition);
			ScreenResolution->AddEditDependencyData(CreatedWindowMode);

			DisplayCategoryCollection->AddChildListData(ScreenResolution);
		}
	}

	// Graphics Category
	{
		UIh_ListDataObject_Collection* GraphicsCategoryCollection = NewObject<UIh_ListDataObject_Collection>();
		GraphicsCategoryCollection->SetDataID(FName("GraphicsCategoryCollection"));
		GraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Graphics")));

		VideoTabCollection->AddChildListData(GraphicsCategoryCollection);

		// Display Gamma
		{
			UIh_ListDataObject_Scalar* DisplayGamma = NewObject<UIh_ListDataObject_Scalar>();
			DisplayGamma->SetDataID(FName("DisplayGamma"));
			DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Display Gamma")));
			DisplayGamma->SetDescriptionRichText(GET_DESCRIPTION("DisplayGammaDescKey"));
			DisplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			DisplayGamma->SetOutputValueRange(TRange<float>(1.7f, 2.7f)); // The default value Unreal has is: 2.2f which is in the middle of 1.7 and 2.7
			DisplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
			DisplayGamma->SetNumberFormattingOptions(UIh_ListDataObject_Scalar::NoDecimal());
			DisplayGamma->SetDefaultValueFromString(LexToString(2.2f));

			DisplayGamma->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentDisplayGamma));
			DisplayGamma->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentDisplayGamma));
			
			GraphicsCategoryCollection->AddChildListData(DisplayGamma);
		}

		UIh_ListDataObject_StringInteger* CreatedOverallQuality = nullptr;
		
		// Overall Quality
		{
			UIh_ListDataObject_StringInteger* OverallQuality = NewObject<UIh_ListDataObject_StringInteger>();
			OverallQuality->SetDataID(FName("OverallQuality"));
			OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
			OverallQuality->SetDescriptionRichText(GET_DESCRIPTION("OverallQualityDescKey"));
			OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));

			OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
			OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));

			OverallQuality->SetShouldApplyChangeImmediately(true);
			
			GraphicsCategoryCollection->AddChildListData(OverallQuality);
			CreatedOverallQuality = OverallQuality;
		}

		// Resolution Scale
		{
			UIh_ListDataObject_Scalar* ResolutionScale = NewObject<UIh_ListDataObject_Scalar>();
			ResolutionScale->SetDataID(FName("ResolutionScale"));
			ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("3D Resolution")));
			ResolutionScale->SetDescriptionRichText(GET_DESCRIPTION("ResolutionScaleDescKey"));
			ResolutionScale->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetOutputValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetDisplayNumericType(ECommonNumericType::Percentage);
			ResolutionScale->SetNumberFormattingOptions(UIh_ListDataObject_Scalar::NoDecimal());

			ResolutionScale->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetResolutionScaleNormalized));
			ResolutionScale->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetResolutionScaleNormalized));

			ResolutionScale->SetShouldApplyChangeImmediately(true);

			ResolutionScale->AddEditDependencyData(CreatedOverallQuality);
			
			GraphicsCategoryCollection->AddChildListData(ResolutionScale);
		}

		// Global Illumination Quality
		{
			UIh_ListDataObject_StringInteger* GlobalIlluminationQuality = NewObject<UIh_ListDataObject_StringInteger>();
			GlobalIlluminationQuality->SetDataID(FName("GlobalIlluminationQuality"));
			GlobalIlluminationQuality->SetDataDisplayName(FText::FromString(TEXT("Global Illumination")));
			GlobalIlluminationQuality->SetDescriptionRichText(GET_DESCRIPTION("GlobalIlluminationQualityDescKey"));
			GlobalIlluminationQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			GlobalIlluminationQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			GlobalIlluminationQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			GlobalIlluminationQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			GlobalIlluminationQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));

			GlobalIlluminationQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGlobalIlluminationQuality));
			GlobalIlluminationQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGlobalIlluminationQuality));

			GlobalIlluminationQuality->SetShouldApplyChangeImmediately(true);

			GlobalIlluminationQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(GlobalIlluminationQuality);
			
			GraphicsCategoryCollection->AddChildListData(GlobalIlluminationQuality);
		}

		// Shadow Quality
		{
			UIh_ListDataObject_StringInteger* ShadowQuality = NewObject<UIh_ListDataObject_StringInteger>();
			ShadowQuality->SetDataID(FName("ShadowQuality"));
			ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("Shadow Quality")));
			ShadowQuality->SetDescriptionRichText(GET_DESCRIPTION("ShadowQualityDescKey"));
			ShadowQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ShadowQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ShadowQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ShadowQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ShadowQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ShadowQuality->SetShouldApplyChangeImmediately(true);

			ShadowQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadowQuality));
			ShadowQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadowQuality));

			ShadowQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(ShadowQuality);
			
			GraphicsCategoryCollection->AddChildListData(ShadowQuality);
		}

		// AntiAliasing Quality
		{
			UIh_ListDataObject_StringInteger* AntiAliasingQuality = NewObject<UIh_ListDataObject_StringInteger>();
			AntiAliasingQuality->SetDataID(FName("AntiAliasingQuality"));
			AntiAliasingQuality->SetDataDisplayName(FText::FromString(TEXT("Anti Aliasing")));
			AntiAliasingQuality->SetDescriptionRichText(GET_DESCRIPTION("AntiAliasingDescKey"));
			AntiAliasingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			AntiAliasingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			AntiAliasingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			AntiAliasingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			AntiAliasingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			AntiAliasingQuality->SetShouldApplyChangeImmediately(true);

			AntiAliasingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAntiAliasingQuality));
			AntiAliasingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAntiAliasingQuality));

			AntiAliasingQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(AntiAliasingQuality);
			
			GraphicsCategoryCollection->AddChildListData(AntiAliasingQuality);
		}

		// View Distance Quality
		{
			UIh_ListDataObject_StringInteger* ViewDistanceQuality = NewObject<UIh_ListDataObject_StringInteger>();
			ViewDistanceQuality->SetDataID(FName("ViewDistanceQuality"));
			ViewDistanceQuality->SetDataDisplayName(FText::FromString(TEXT("View Distance")));
			ViewDistanceQuality->SetDescriptionRichText(GET_DESCRIPTION("ViewDistanceDescKey"));
			ViewDistanceQuality->AddIntegerOption(0, FText::FromString(TEXT("Near")));
			ViewDistanceQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ViewDistanceQuality->AddIntegerOption(2, FText::FromString(TEXT("Far")));
			ViewDistanceQuality->AddIntegerOption(3, FText::FromString(TEXT("Very Far")));
			ViewDistanceQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ViewDistanceQuality->SetShouldApplyChangeImmediately(true);

			ViewDistanceQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetViewDistanceQuality));
			ViewDistanceQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetViewDistanceQuality));

			ViewDistanceQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(ViewDistanceQuality);
			
			GraphicsCategoryCollection->AddChildListData(ViewDistanceQuality);
		}

		// Texture Quality
		{
			UIh_ListDataObject_StringInteger* TextureQuality = NewObject<UIh_ListDataObject_StringInteger>();
			TextureQuality->SetDataID(FName("TextureQuality"));
			TextureQuality->SetDataDisplayName(FText::FromString(TEXT("Texture Quality")));
			TextureQuality->SetDescriptionRichText(GET_DESCRIPTION("TextureQualityDescKey"));
			TextureQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			TextureQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			TextureQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			TextureQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			TextureQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			TextureQuality->SetShouldApplyChangeImmediately(true);

			TextureQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetTextureQuality));
			TextureQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetTextureQuality));

			TextureQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(TextureQuality);
			
			GraphicsCategoryCollection->AddChildListData(TextureQuality);
		}

		// Visual Effects Quality
		{
			UIh_ListDataObject_StringInteger* VisualEffectQuality = NewObject<UIh_ListDataObject_StringInteger>();
			VisualEffectQuality->SetDataID(FName("VisualEffectQuality"));
			VisualEffectQuality->SetDataDisplayName(FText::FromString(TEXT("Visual Effect Quality")));
			VisualEffectQuality->SetDescriptionRichText(GET_DESCRIPTION("VisualEffectQualityDescKey"));
			VisualEffectQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			VisualEffectQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			VisualEffectQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			VisualEffectQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			VisualEffectQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			VisualEffectQuality->SetShouldApplyChangeImmediately(true);

			VisualEffectQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetVisualEffectQuality));
			VisualEffectQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVisualEffectQuality));

			VisualEffectQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(VisualEffectQuality);
			
			GraphicsCategoryCollection->AddChildListData(VisualEffectQuality);
		}

		// Reflection Quality
		{
			UIh_ListDataObject_StringInteger* ReflectionQuality = NewObject<UIh_ListDataObject_StringInteger>();
			ReflectionQuality->SetDataID(FName("ReflectionQuality"));
			ReflectionQuality->SetDataDisplayName(FText::FromString(TEXT("Reflection Quality")));
			ReflectionQuality->SetDescriptionRichText(GET_DESCRIPTION("ReflectionQualityDescKey"));
			ReflectionQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ReflectionQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ReflectionQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ReflectionQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ReflectionQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ReflectionQuality->SetShouldApplyChangeImmediately(true);

			ReflectionQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetReflectionQuality));
			ReflectionQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetReflectionQuality));

			ReflectionQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(ReflectionQuality);
			
			GraphicsCategoryCollection->AddChildListData(ReflectionQuality);
		}

		// Post-Processing Quality
		{
			UIh_ListDataObject_StringInteger* PostProcessingQuality = NewObject<UIh_ListDataObject_StringInteger>();
			PostProcessingQuality->SetDataID(FName("PostProcessingQuality"));
			PostProcessingQuality->SetDataDisplayName(FText::FromString(TEXT("Post-Processing Quality")));
			PostProcessingQuality->SetDescriptionRichText(GET_DESCRIPTION("PostProcessingQualityDescKey"));
			PostProcessingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			PostProcessingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			PostProcessingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			PostProcessingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			PostProcessingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			PostProcessingQuality->SetShouldApplyChangeImmediately(true);

			PostProcessingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetPostProcessingQuality));
			PostProcessingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetPostProcessingQuality));

			PostProcessingQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(PostProcessingQuality);
			
			GraphicsCategoryCollection->AddChildListData(PostProcessingQuality);
		}
	}

	// Advanced Graphics Category
	{
		UIh_ListDataObject_Collection* AdvancedGraphicsCategoryCollection = NewObject<UIh_ListDataObject_Collection>();
		AdvancedGraphicsCategoryCollection->SetDataID(FName("AdvancedGraphicsCategoryCollection"));
		AdvancedGraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Advanced Graphics")));

		VideoTabCollection->AddChildListData(AdvancedGraphicsCategoryCollection);

		// Vertical Sync
		{
			UIh_ListDataObject_StringBool* VerticalSync = NewObject<UIh_ListDataObject_StringBool>();
			VerticalSync->SetDataID(FName("VerticalSync"));
			VerticalSync->SetDataDisplayName(FText::FromString(TEXT("V-Sync")));
			VerticalSync->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
			VerticalSync->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
			VerticalSync->SetDescriptionRichText(GET_DESCRIPTION("VerticalSyncDescKey"));
			VerticalSync->SetFalseAsDefaultValue();
			VerticalSync->SetShouldApplyChangeImmediately(true);

			VerticalSync->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(IsVSyncEnabled));
			VerticalSync->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVSyncEnabled));

			FOptionsDataEditConditionDescriptor FullscreenOnlyCondition;
			FullscreenOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This feature only works if the 'Window Mode' is set to 'Fullscreen'.</>"));
			FullscreenOnlyCondition.SetForcedStringValue(TEXT("false"));
			FullscreenOnlyCondition.SetEditConditionFunc([CreatedWindowMode]()->bool
			{
				return CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::Fullscreen;
			});

			VerticalSync->AddEditCondition(FullscreenOnlyCondition);

			AdvancedGraphicsCategoryCollection->AddChildListData(VerticalSync);
		}

		// Frame Rate Limit
		{
			UIh_ListDataObject_String* FrameRateLimit = NewObject<UIh_ListDataObject_String>();
			FrameRateLimit->SetDataID(FName("FrameRateLimit"));
			FrameRateLimit->SetDataDisplayName(FText::FromString(TEXT("Frame Rate Limit")));
			FrameRateLimit->SetDescriptionRichText(GET_DESCRIPTION("FrameRateLimitDescKey"));
			FrameRateLimit->AddDynamicOption(LexToString(30.f), FText::FromString(TEXT("30 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(60.f), FText::FromString(TEXT("60 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(90.f), FText::FromString(TEXT("90 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(120.f), FText::FromString(TEXT("120 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(0.f), FText::FromString(TEXT("No Limit")));
			FrameRateLimit->SetDefaultValueFromString(LexToString(0.f));
			FrameRateLimit->SetShouldApplyChangeImmediately(true);

			FrameRateLimit->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFrameRateLimit));
			FrameRateLimit->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFrameRateLimit));
			
			AdvancedGraphicsCategoryCollection->AddChildListData(FrameRateLimit);
		}
	}
	
	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UIh_OptionsDataRegistry::InitControlCollectionTab()
{
	UIh_ListDataObject_Collection* ControlTabCollection = NewObject<UIh_ListDataObject_Collection>();
	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}
