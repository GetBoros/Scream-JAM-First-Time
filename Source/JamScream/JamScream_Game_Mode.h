#pragma once

#include "Blueprint/UserWidget.h"

#include "GameFramework/GameModeBase.h"
#include "JamScream_Game_Mode.generated.h"

// Определение enum class
UENUM(BlueprintType) enum class EOption_Type : uint8
{
	EPT_None UMETA(DisplayName = "EPT_None"),
	EPT_Window_Mode UMETA(DisplayName = "EPT_Window_Mode"),
	EPT_Quality_Presset UMETA(DisplayName = "EPT_Quality_Presset"),
	EPT_Quality_Shadows UMETA(DisplayName = "EPT_Quality_Shadows"),
	EPT_Quality_Foliage UMETA(DisplayName = "EPT_Quality_Foliage"),
	EPT_Quality_Texture UMETA(DisplayName = "EPT_Quality_Texture"),
	EPT_Quality_Shading UMETA(DisplayName = "EPT_Quality_Shading"),
	EPT_Quality_Reflection UMETA(DisplayName = "EPT_Quality_Reflection"),
	EPT_Quality_Anti_Aliasing UMETA(DisplayName = "EPT_Quality_Anti_Aliasing"),
	EPT_Quality_Visual_Effects UMETA(DisplayName = "EPT_Quality_Visual_Effects"),
	EPT_Quality_View_Distances UMETA(DisplayName = "EPT_Quality_View_Distances"),
	EPT_Quality_Post_Processing UMETA(DisplayName = "EPT_Quality_Post_Processing"),
	EPT_Quality_Global_Illumination_Quality UMETA(DisplayName = "EPT_Quality_Global_Illumination_Quality"),
	EPT_Frame_Rate UMETA(DisplayName = "EPT_Frame_Rate"),
	EPT_Screen_Resolution UMETA(DisplayName = "EPT_Screen_Resolution"),
	EPT_Screen_Percentage UMETA(DisplayName = "EPT_Screen_Percentage"),
	EPT_Toogle_Directx UMETA(DisplayName = "EPT_Toogle_Directx"),
	EPT_Show_Frame_Per_Sec UMETA(DisplayName = "EPT_Show_Frame_Per_Sec")
};

// UADrag_Widget
UCLASS(meta = (DisableNativeTick)) class UJamScreen_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	UFUNCTION(BlueprintCallable) void Update_Options() const;
	
	UFUNCTION(BlueprintCallable) void Toogle_DirectX() const;
	UFUNCTION(BlueprintCallable) void Set_Screen_Percentage() const;
	UFUNCTION(BlueprintCallable) void Set_Screen_Resolution() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) int Widget_Index;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) EOption_Type Option_Type;

	// TASKS
	/*
		- Create Button
			- This button need to be redrawed
			- She has name and index
			- ...
		- Store array of buttons to redraw active and else if needed
	*/
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
