// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Components/Ih_CommonRotator.h"
#include "CommonTextBlock.h"

void UIh_CommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	const int32 Index = TextLabels.IndexOfByPredicate(
	[InTextOption](const FText& TextItem)
		{
			return TextItem.EqualTo(InTextOption);
		}
	);

	if (Index != INDEX_NONE)
	{
		SetSelectedItem(Index);
	}
	else
	{
		MyText->SetText(InTextOption);
	}
}
