// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/Ih_ListDataObject_Collection.h"

void UIh_OptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

void UIh_OptionsDataRegistry::InitGameplayCollectionTab()
{
	UIh_ListDataObject_Collection* GameplayTabCollection = NewObject<UIh_ListDataObject_Collection>();
	GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));

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
