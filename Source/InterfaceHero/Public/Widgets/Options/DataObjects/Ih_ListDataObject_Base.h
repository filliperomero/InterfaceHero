// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ih_ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; }

UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:
	void InitDataObject();
	/** Empty in base class. Child class ListDataObject_Collection should override it.
	 * The function should return all the child data a tab has
	 */
	virtual TArray<UIh_ListDataObject_Base*> GetAllChildListData() const { return TArray<UIh_ListDataObject_Base*>(); }
	virtual bool HasAnyChildListData() const { return false; }

protected:
	// TEmpty in base class. he Child classes should override it to handle the initialization needed accordingly
	virtual void OnDataObjectInitialized();

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UIh_ListDataObject_Base> ParentData;

public:
	LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledRichText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	LIST_DATA_ACCESSOR(TObjectPtr<UIh_ListDataObject_Base>, ParentData);
};
