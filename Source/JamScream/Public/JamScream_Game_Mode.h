#pragma once

#include "Menu_Main_Config.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "JamScream_Game_Mode.generated.h"

// EOption_Type
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
//-----------------------------------------------------------------------------------------------------------




// UAMenu_Main_Setting_Button
class UTextBlock;
class UButton;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAMenu_Main_Setting_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	void Init();

	void Toogle_DirectX() const;
	void Set_Screen_Percentage() const;
	void Set_Screen_Resolution() const;

	UWidget **Buttons_Settings_Array;

	void Update_State() const;
	UFUNCTION(BlueprintCallable) void Set_Button_State(bool is_button_active);
	UFUNCTION() void Button_Pressed();  // OnButtonPressed event

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) EOption_Type Option_Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) int Widget_Index;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) FText Button_Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UButton *Button;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text;

};
//-----------------------------------------------------------------------------------------------------------




// UAMenu_Main_Settings
class USpinBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAMenu_Main_Settings : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	UWidget *Button_Array[Menu_Main_Config::Button_Setting_Count] {};  // Stored Max 5 Buttons || 5 Buttons is Max

	UFUNCTION() void Handle_Spin_Box(float test);

	UFUNCTION(BlueprintCallable) void Button_Array_Emplace(const int button_index, UWidget *button_widget);  // Add Widget to Array
	UFUNCTION(BlueprintCallable) void Button_Active_Draw();  // Add Widget to Array
	UFUNCTION(BlueprintCallable) void Button_Spin_Box_Update();  // Update Button marked with spinned box

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) bool Is_Spin_Box;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) EOption_Type Button_Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) TSubclassOf<UUserWidget> Button_Class;;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) USpinBox *Spin_Box_Root;
};
//-----------------------------------------------------------------------------------------------------------




// AJamScreamGameMode
UCLASS(minimalapi) class AJamScream_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJamScream_Game_Mode();
};
//-----------------------------------------------------------------------------------------------------------
