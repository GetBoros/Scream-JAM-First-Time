#include "JamScream_Game_Mode.h"

#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SpinBox.h"
#include "Misc/ConfigCacheIni.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

// UAMenu_Main_Setting_Button
void UAMenu_Main_Setting_Button::NativeConstruct()
{
    Super::NativeConstruct();
    Init();
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Init()
{
    if (Button_Name.IsEmpty() )  // If not added name use default name
        Button_Name = FText::FromName(Menu_Main_Config::Button_Name_Defaults[Widget_Index]);  // Set Name | Default Buttons
    Button_Text->SetText(Button_Name);  // Set Name to Button in curr widget

    if (!Button != 0)  // if don`t excist don`t bind button
        return;
    Button->OnPressed.AddDynamic(this, &UAMenu_Main_Setting_Button::Button_Pressed);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Toogle_DirectX() const
{
    FString config_path = FPaths::ProjectConfigDir() + TEXT("DefaultEngine.ini");
    FString current_rhi;

    if (GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), current_rhi, config_path) )  // Get current DXT
        if (current_rhi == TEXT("DefaultGraphicsRHI_DX12") )  // Toogle DX
            GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), TEXT("DefaultGraphicsRHI_DX11"), config_path);
        else
            GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), TEXT("DefaultGraphicsRHI_DX12"), config_path);

    GConfig->Flush(false, config_path);  // Save to config
    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("quit") );  // Exit from game
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Set_Screen_Percentage() const
{
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();
    if (!user_settings != 0)
        return;

    switch (Widget_Index)
    {
    case 0:
        user_settings->SetResolutionScaleValueEx(50);
        break;
    case 1:
        user_settings->SetResolutionScaleValueEx(75);
        break;
    case 2:
        user_settings->SetResolutionScaleValueEx(100);
        break;
    default:
        user_settings->SetResolutionScaleValueEx(50);
        break;
    }
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Set_Screen_Resolution() const
{
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();
    if (!user_settings != 0)
        return;

    user_settings->SetScreenResolution(Menu_Main_Config::Screen_Resolution_Array[Widget_Index]);
    user_settings->SetFullscreenMode(EWindowMode::Fullscreen);
    // Need redraw prev button
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Set_Button_State(bool is_button_active)
{
    Button->SetBackgroundColor(is_button_active ? Menu_Main_Config::Button_Active : Menu_Main_Config::Button_Inactive);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Update_State() const
{
    int i = 0;
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();
    UAMenu_Main_Setting_Button *menu_main_setting_button = 0;

    if (!user_settings != 0)
        return;

    switch (Option_Type)
    {
    case EOption_Type::EPT_None:
        return;
        break;
    case EOption_Type::EPT_Window_Mode:
        user_settings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(Widget_Index) );
        user_settings->ApplyResolutionSettings(false);
        break;
    case EOption_Type::EPT_Quality_Presset:
        user_settings->SetOverallScalabilityLevel(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Shadows:
        user_settings->SetShadowQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Foliage:
        user_settings->SetFoliageQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Texture:
        user_settings->SetTextureQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Shading:
        user_settings->SetShadingQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Reflection:
        user_settings->SetReflectionQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Anti_Aliasing:
        user_settings->SetAntiAliasingQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Visual_Effects:
        user_settings->SetVisualEffectQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_View_Distances:
        user_settings->SetViewDistanceQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Post_Processing:
        user_settings->SetPostProcessingQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Global_Illumination_Quality:
        user_settings->SetGlobalIlluminationQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Frame_Rate:
        user_settings->SetFrameRateLimit(30);
        break;
    case EOption_Type::EPT_Screen_Resolution:
        Set_Screen_Resolution();
        break;
    case EOption_Type::EPT_Screen_Percentage:
        Set_Screen_Percentage();
        break;
    case EOption_Type::EPT_Toogle_Directx:
        Toogle_DirectX();
        break;
    case EOption_Type::EPT_Show_Frame_Per_Sec:
        UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("stat fps") );  // Exit from game
        break;
    default:
        break;
    }
 
    user_settings->ApplySettings(false);
    for (i = 0; i < 5; i++)
    {
        if (!(Buttons_Settings_Array[i] != 0) )
            return;
        menu_main_setting_button = Cast<UAMenu_Main_Setting_Button>(Buttons_Settings_Array[i]);
        menu_main_setting_button->Set_Button_State(false);
    }
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Button_Pressed()
{
    Update_State();
    Set_Button_State(true);
}
//------------------------------------------------------------------------------------------------------------




// UAMenu_Main_Settings
void UAMenu_Main_Settings::NativeConstruct()
{
	
    Super::NativeConstruct();

    Init();
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Init()
{

    Menu_Settings_Name->SetText(Menu_Settings_Text);  // Set Setting Name
    Spin_Box_Root->SetVisibility(ESlateVisibility::Collapsed);  // Hide if not check in BP

    if (Is_Spin_Box)
        Button_Spin_Box_Update();  // Init Spin Box settings
    else
        Button_Create_Default();
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Clear_Memmory()
{
    Button_Array[0]->RemoveFromParent();
    Button_Array[0]->ConditionalBeginDestroy();
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Button_Create_Default()
{
    int i = 0;
    UAMenu_Main_Setting_Button *array_buttons[Menu_Main_Config::Button_Setting_Count]{};  // !!! Mem leak

    if (Buttons_Name.Num() < 1)  // If names was added in BP
    {
        Buttons_Name.SetNum(Buttons_Count);  // Create and init to none array FText
        Buttons_Name[i] = FText::FromName(Menu_Main_Config::Button_Name_Defaults[i]);  // Set default Name
    }

    for (i = 0; i < Buttons_Count; i++)
    {
        array_buttons[i] = CreateWidget<UAMenu_Main_Setting_Button>(this, Button_Class);
        array_buttons[i]->Option_Type = Button_Type;
        array_buttons[i]->Widget_Index = i;
        array_buttons[i]->Button_Name = Buttons_Name[i];

        Horizontal_Box_List->AddChild(array_buttons[i]);  // Add widget as child to horrizontal box

        Button_Array[i] = array_buttons[i];
        array_buttons[i]->Buttons_Settings_Array = Button_Array;
    }
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Handle_Spin_Box(float test)
{
    UGameUserSettings *user_settings;

    user_settings = GEngine->GetGameUserSettings();

    if (Button_Type == EOption_Type::EPT_Frame_Rate)
        user_settings->SetFrameRateLimit(FMath::Clamp(test, 24.0f, 144.0f) );
    if (Button_Type == EOption_Type::EPT_Screen_Percentage)
        user_settings->SetResolutionScaleNormalized(FMath::Clamp(test, 0.2f, 1.0f) );

    Spin_Box_Root->SetValue(test);
    user_settings->ApplySettings(false);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Button_Array_Emplace(const int button_index, UWidget *button_widget)
{
    UAMenu_Main_Setting_Button *menu_main_setting_button;

    Button_Array[button_index] = button_widget;  // Store button widget ptr, use to redraw button
    menu_main_setting_button = Cast<UAMenu_Main_Setting_Button>(button_widget);
    menu_main_setting_button->Buttons_Settings_Array = Button_Array;  // store in button widget parent ptr
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Button_Active_Draw()
{
    int i, button_index;
    FIntPoint int_point;
    UGameUserSettings *user_settings;
    UAMenu_Main_Setting_Button *menu_main_setting_button;

    i = 0;
    button_index = 0;
    int_point = {};
    user_settings = GEngine->GetGameUserSettings();
    if (!user_settings != 0)
        return;

    switch (Button_Type)
    {// For current button type have unique button setting

    case EOption_Type::EPT_None:
        break;
    case EOption_Type::EPT_Window_Mode:
        button_index = (EWindowMode::Type)user_settings->GetDefaultWindowMode();
        break;
    case EOption_Type::EPT_Quality_Presset:
        button_index = user_settings->GetOverallScalabilityLevel();
        break;
    case EOption_Type::EPT_Quality_Shadows:
        button_index = user_settings->GetShadowQuality();
        break;
    case EOption_Type::EPT_Quality_Foliage:
        button_index = user_settings->GetFoliageQuality();
        break;
    case EOption_Type::EPT_Quality_Texture:
        button_index = user_settings->GetTextureQuality();
        break;
    case EOption_Type::EPT_Quality_Shading:
        button_index = user_settings->GetShadingQuality();
        break;
    case EOption_Type::EPT_Quality_Reflection:
        button_index = user_settings->GetReflectionQuality();
        break;
    case EOption_Type::EPT_Quality_Anti_Aliasing:
        button_index = user_settings->GetAntiAliasingQuality();
        break;
    case EOption_Type::EPT_Quality_Visual_Effects:
        button_index = user_settings->GetVisualEffectQuality();
        break;
    case EOption_Type::EPT_Quality_View_Distances:
        button_index = user_settings->GetViewDistanceQuality();
        break;
    case EOption_Type::EPT_Quality_Post_Processing:
        button_index = user_settings->GetPostProcessingQuality();
        break;
    case EOption_Type::EPT_Quality_Global_Illumination_Quality:
        button_index = user_settings->GetGlobalIlluminationQuality();
        break;
    case EOption_Type::EPT_Screen_Resolution:
    {// Find current screen resolution | need to redraw current setting

        int_point = user_settings->GetScreenResolution();
        for (i = 0; i < Menu_Main_Config::Screen_Resolution_Array_Size; i++)
            if (Menu_Main_Config::Screen_Resolution_Array[i] == int_point)
                button_index = i;
        break;
    }
    default:
        button_index = 0;
        break;
    }

    if (button_index > 5 || button_index < 0)
        button_index = 0;
    if (!(Button_Array != 0) )
        return;
    menu_main_setting_button = Cast<UAMenu_Main_Setting_Button>(Button_Array[button_index] );  // !!! Empty
    menu_main_setting_button->Set_Button_State(true);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Button_Spin_Box_Update()
{
    UGameUserSettings *user_settings;

    if (!Is_Spin_Box)
        return;

    user_settings = GEngine->GetGameUserSettings();
    Spin_Box_Root->SetVisibility(ESlateVisibility::Visible);

    if (Button_Type == EOption_Type::EPT_Frame_Rate)
        Spin_Box_Root->SetValue(user_settings->GetFrameRateLimit() );
    if (Button_Type == EOption_Type::EPT_Screen_Percentage)
    {
        Spin_Box_Root->SetMinValue(0.0f);
        Spin_Box_Root->SetMaxValue(1.0f);
        Spin_Box_Root->SetMinSliderValue(0.1f);
        Spin_Box_Root->SetMaxSliderValue(1.0f);
        Spin_Box_Root->SetToolTipText(FText::FromString("From 0.0 to 1.0") );
        Spin_Box_Root->SetValue(user_settings->GetResolutionScaleNormalized());
    }

    Spin_Box_Root->OnValueChanged.AddDynamic(this, &UAMenu_Main_Settings::Handle_Spin_Box);
}
//------------------------------------------------------------------------------------------------------------




// AJamScream_Game_Mode
AJamScream_Game_Mode::AJamScream_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------
