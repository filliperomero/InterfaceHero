// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ih_OptionsDataRegistry.generated.h"

class UIh_ListDataObject_Base;
class UIh_ListDataObject_Collection;

UCLASS()
class INTERFACEHERO_API UIh_OptionsDataRegistry : public UObject
{
	GENERATED_BODY()

public:
	// Called by options screen right after the object of type OptionsDataRegistry is created
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);
	TArray<UIh_ListDataObject_Base*> GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const;

private:
	void FindChildListDataRecursively(UIh_ListDataObject_Base* InParentData, TArray<UIh_ListDataObject_Base*>& OutChildListData) const;
	
	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab(ULocalPlayer* InOwningLocalPlayer);

	UPROPERTY(Transient)
	TArray<UIh_ListDataObject_Collection*> RegisteredOptionsTabCollections;

public:
	const TArray<UIh_ListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections; }
};
