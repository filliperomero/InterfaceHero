// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_KeyRemapScreen.h"

#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor : public IInputProcessor
{
protected:
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override
	{
	}

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		return true;
	}

	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
	{
		return true;
	}
};

void UIh_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	InputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>();

	FSlateApplication::Get().RegisterInputPreProcessor(InputPreprocessor, -1);
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
