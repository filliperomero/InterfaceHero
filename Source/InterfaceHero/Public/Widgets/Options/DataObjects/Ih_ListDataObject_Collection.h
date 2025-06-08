// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListDataObject_Base.h"
#include "Ih_ListDataObject_Collection.generated.h"

UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_Collection : public UIh_ListDataObject_Base
{
	GENERATED_BODY()

public:
	virtual TArray<UIh_ListDataObject_Base*> GetAllChildListData() const override;
	virtual bool HasAnyChildListData() const override;

	void AddChildListData(UIh_ListDataObject_Base* InChildListData);

private:
	UPROPERTY(Transient)
	TArray<UIh_ListDataObject_Base*> ChildListDataArray;
};
