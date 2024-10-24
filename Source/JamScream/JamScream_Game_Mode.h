#pragma once

#include "Blueprint/UserWidget.h"

#include "GameFramework/GameModeBase.h"
#include "JamScream_Game_Mode.generated.h"

// UADrag_Widget
UCLASS(meta = (DisableNativeTick)) class UJamScreen_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	UFUNCTION(BlueprintCallable) void Toogle_DirectX();
	UFUNCTION(BlueprintCallable) void Set_Screen_Percentage(const int button_index);
	UFUNCTION(BlueprintCallable) void Set_Screen_Resolution(const int button_index);
};
//-----------------------------------------------------------------------------------------------------------         





// AJamScreamGameMode
UCLASS(minimalapi) class AJamScream_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJamScream_Game_Mode();
};
//------------------------------------------------------------------------------------------------------------
