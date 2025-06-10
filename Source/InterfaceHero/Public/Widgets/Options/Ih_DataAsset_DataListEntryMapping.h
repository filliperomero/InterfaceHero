// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Ih_DataAsset_DataListEntryMapping.generated.h"

class UIh_ListEntry_Base;
class UIh_ListDataObject_Base;

UCLASS()
class INTERFACEHERO_API UIh_DataAsset_DataListEntryMapping : public UDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<UIh_ListEntry_Base> FindEntryWidgetClassByDataObject(UIh_ListDataObject_Base* InDataObject) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UIh_ListDataObject_Base>, TSubclassOf<UIh_ListEntry_Base>> DataObjectListEntryMap;
};
