// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringResolution.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Settings/Ih_GameUserSettings.h"

void UIh_ListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> OutAvailableResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(OutAvailableResolutions);

	// Lowest to Highest
	OutAvailableResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)->bool
		{
			return A.SizeSquared() < B.SizeSquared();
		}
	);

	for (const FIntPoint& Resolution : OutAvailableResolutions)
	{
		AddDynamicOption(ResolutionToValueString(Resolution), ResolutionToDisplayText(Resolution));
	}

	MaximumAllowedResolution = ResolutionToValueString(OutAvailableResolutions.Last());

	SetDefaultValueFromString(MaximumAllowedResolution);
}

void UIh_ListDataObject_StringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = ResolutionToDisplayText(UIh_GameUserSettings::Get()->GetScreenResolution());
	}
}

FString UIh_ListDataObject_StringResolution::ResolutionToValueString(const FIntPoint& InResolution)
{
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UIh_ListDataObject_StringResolution::ResolutionToDisplayText(const FIntPoint& InResolution)
{
	const FString DisplayString = FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y);
	return FText::FromString(DisplayString);
}
