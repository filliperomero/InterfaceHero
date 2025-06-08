// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Components/Ih_TabListWidgetBase.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/Ih_CommonButtonBase.h"

void UIh_TabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
}

#if WITH_EDITOR
void UIh_TabListWidgetBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ") +
			GetClass()->GetName() +
			TEXT(" needs a valid entry widget class to function properly")
		));
	}
}
#endif

