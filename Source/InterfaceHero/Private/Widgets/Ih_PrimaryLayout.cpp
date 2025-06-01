// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Ih_PrimaryLayout.h"
#include "Ih_DebugHelper.h"

UCommonActivatableWidgetContainerBase* UIh_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InStackTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InStackTag), TEXT("Cannot find the widget stack by the tag %s"), *InStackTag.ToString())

	return RegisteredWidgetStackMap.FindRef(InStackTag);
}

void UIh_PrimaryLayout::RegisterWidgetStack(UPARAM(meta=(Categories="WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InWidgetStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InWidgetStack);

			Debug::Print(TEXT("Widget Stack Registered under the tag ") + InStackTag.ToString());
		}
	}
}
