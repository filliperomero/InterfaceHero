// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "Ih_TabListWidgetBase.generated.h"

class UIh_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_TabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

public:
	void RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName);

private:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IH - Tab List Settings", meta=(AllowPrivateAccess="true", ClampMin="1", ClampMax="10"))
	int32 DebugEditorPreviewTabCount { 3 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IH - Tab List Settings", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UIh_CommonButtonBase> TabButtonEntryWidgetClass;
};
