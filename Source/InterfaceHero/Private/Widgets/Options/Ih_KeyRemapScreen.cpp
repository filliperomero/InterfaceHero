// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_KeyRemapScreen.h"
#include "CommonInputTypeEnum.h"
#include "CommonRichTextBlock.h"
#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor : public IInputProcessor
{
public:
	FKeyRemapScreenInputPreprocessor(const ECommonInputType InInputTypeToListenTo)
		: InputTypeToListenTo(InInputTypeToListenTo)
	{ }

	DECLARE_DELEGATE_OneParam(FOnInputPreProcessorKeySelectCanceledDelegate, const FString&/*CanceledReason*/)
	DECLARE_DELEGATE_OneParam(FOnInputPreProcessorKeyPressedDelegate, const FKey&/*PressedKey*/);
	
	FOnInputPreProcessorKeyPressedDelegate OnInputPreProcessorKeyPressed;
	FOnInputPreProcessorKeySelectCanceledDelegate OnInputPreProcessorKeySelectCanceled;
protected:
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override
	{ }

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		ProcessPressedKey(InKeyEvent.GetKey());
		return true;
	}

	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
	{
		ProcessPressedKey(MouseEvent.GetEffectingButton());
		return true;
	}

	void ProcessPressedKey(const FKey& InPressedKey)
	{
		if (InPressedKey == EKeys::Escape)
		{
			OnInputPreProcessorKeySelectCanceled.ExecuteIfBound(TEXT("Key Remap has been canceled"));

			return;
		}

		switch (InputTypeToListenTo)
		{
		case ECommonInputType::MouseAndKeyboard:
			if (InPressedKey.IsGamepadKey())
			{
				OnInputPreProcessorKeySelectCanceled.ExecuteIfBound(TEXT("Detected Gamepad Key pressed for Keyboard Inputs. Key Remap has been canceled."));
				return;
			}
			break;
		case ECommonInputType::Gamepad:
			if (!InPressedKey.IsGamepadKey())
			{
				OnInputPreProcessorKeySelectCanceled.ExecuteIfBound(TEXT("Detected Keyboard/Mouse Key pressed for Gamepad Inputs. Key Remap has been canceled."));
				return;
			}
			break;
		default:
			break;
		}

		OnInputPreProcessorKeyPressed.ExecuteIfBound(InPressedKey);
	}

private:
	ECommonInputType InputTypeToListenTo;
};

void UIh_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	InputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(DesiredInputType);
	InputPreprocessor->OnInputPreProcessorKeyPressed.BindUObject(this, &ThisClass::OnValidKeyPressedDetected);
	InputPreprocessor->OnInputPreProcessorKeySelectCanceled.BindUObject(this, &ThisClass::OnKeySelectedCanceled);

	FSlateApplication::Get().RegisterInputPreProcessor(InputPreprocessor, -1);

	FString InputDeviceName;

	switch (DesiredInputType) {
	case ECommonInputType::MouseAndKeyboard:
		InputDeviceName = TEXT("Mouse & Keyboard");
		break;
	case ECommonInputType::Gamepad:
		InputDeviceName = TEXT("Gamepad");
		break;
	default:
		break;
	}

	const FString DisplayRichMessage = FString::Printf(TEXT("<KeyRemapDefault>Press any</> <KeyRemapHighlight>%s</> <KeyRemapDefault>key.</>"), *InputDeviceName);

	CommonRichText_RemapMessage->SetText(FText::FromString(DisplayRichMessage));
}

void UIh_KeyRemapScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (InputPreprocessor.IsValid())
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(InputPreprocessor);

		InputPreprocessor.Reset();
	}
}

void UIh_KeyRemapScreen::OnValidKeyPressedDetected(const FKey& PressedKey)
{
	RequestDeactivateWidget(
		[this, PressedKey]()
		{
			OnKeyRemapScreenKeyPressed.ExecuteIfBound(PressedKey);
		}
	);
}

void UIh_KeyRemapScreen::OnKeySelectedCanceled(const FString& CanceledReason)
{
	RequestDeactivateWidget(
		[this, CanceledReason]()
		{
			OnKeyRemapScreenKeySelectCanceled.ExecuteIfBound(CanceledReason);
		}
	);
}

void UIh_KeyRemapScreen::RequestDeactivateWidget(TFunction<void()> PreDeactivateCallback)
{
	// Delay a tick to make sure the input is processed correctly
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda(
			[PreDeactivateCallback, this](float DeltaTime)->bool
			{
				PreDeactivateCallback();

				DeactivateWidget();

				// false will stop the "ticking"
				return false;
			}
		)
	);
}

void UIh_KeyRemapScreen::SetDesiredInputTypeToFilter(const ECommonInputType InDesiredInputType)
{
	DesiredInputType = InDesiredInputType;
}
