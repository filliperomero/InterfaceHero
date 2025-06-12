// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class EIh_ConfirmScreenType : uint8
{
	Ok,
	YesNo,
	OkCancel,
	Unknown UMETA(Hidden),
};

UENUM(BlueprintType)
enum class EIh_ConfirmScreenButtonType : uint8
{
	Confirmed,
	Cancelled,
	Closed,
	Unknown UMETA(Hidden),
};

UENUM(BlueprintType)
enum class EIh_OptionsListDataModifyReason : uint8
{
	DirectlyModified,
	DependencyModified,
	ResetToDefault
};