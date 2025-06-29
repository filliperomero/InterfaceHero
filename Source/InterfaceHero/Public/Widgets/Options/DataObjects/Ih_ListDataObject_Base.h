// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types/Ih_EnumTypes.h"
#include "Types/Ih_StructTypes.h"
#include "UObject/Object.h"
#include "Ih_ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; }

UCLASS(Abstract)
class INTERFACEHERO_API UIh_ListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:	
	void InitDataObject();
	/** Empty in base class. Child class ListDataObject_Collection should override it. The function should return all the child data a tab has */
	virtual TArray<UIh_ListDataObject_Base*> GetAllChildListData() const { return TArray<UIh_ListDataObject_Base*>(); }
	virtual bool HasAnyChildListData() const { return false; }
	
	/** Child class should override them to provide implementations for resetting the data */
	virtual bool HasDefaultValue() const { return false; }
	virtual bool CanResetBackToDefaultValue() const { return false; }
	virtual bool TryResetBackToDefaultValue() { return false; }

	/** Gets Called from OptionsDataRegistry for adding in edit conditions for the constructed list data objects */
	void AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition);
	
	bool IsDataCurrentlyEditable();

protected:
	// Empty in base class. The Child classes should override it to handle the initialization needed accordingly
	virtual void OnDataObjectInitialized();

	virtual void NotifyListDataModified(UIh_ListDataObject_Base* ModifiedData, EIh_OptionsListDataModifyReason ModifyReason = EIh_OptionsListDataModifyReason::DirectlyModified);

	/** Child class should override this to allow the value to be set to the forced string value */
	virtual bool CanSetToForcedStringValue(const FString& InForcedValue) const { return false; }

	/** Child class should override this to specify how to set the current value to the forced value */
	virtual void OnSetToForcedStringValue(const FString& InForcedValue) {}

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UIh_ListDataObject_Base> ParentData;

	bool bShouldApplyChangeImmediately { false };

	UPROPERTY(Transient)
	TArray<FOptionsDataEditConditionDescriptor> EditConditionDescArray;
	
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UIh_ListDataObject_Base*/*ModifiedData*/, EIh_OptionsListDataModifyReason/*ModifyReason*/);
	FOnListDataModifiedDelegate OnListDataModified;

	void SetShouldApplyChangeImmediately(bool bShouldApply) { bShouldApplyChangeImmediately = bShouldApply; }
	
	LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledRichText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	LIST_DATA_ACCESSOR(TObjectPtr<UIh_ListDataObject_Base>, ParentData);
};
