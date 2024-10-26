#include "JamScream_Game_Mode.h"

#include "Components/SpinBox.h"
#include "Misc/ConfigCacheIni.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

// UAMenu_Main_Setting_Button
void UAMenu_Main_Setting_Button::NativeConstruct()
{
    Super::NativeConstruct();
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
    FIntPoint point {};
    
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();
    if (!user_settings != 0)
        return;

    switch (Widget_Index)
    {
    case 0:
        point = FIntPoint(960, 540);
        break;
    case 1:
        point = FIntPoint(1280, 720);
        break;
    case 2:
        point = FIntPoint(1920, 1080);
        break;
    default:
        point = FIntPoint(960, 540);
        break;
    }
    user_settings->SetScreenResolution(point);
    user_settings->SetFullscreenMode(EWindowMode::Fullscreen);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Init()
{
    FName names[5] = { L"1", L"2", L"3", L"4", L"5"};  // !!! To Config
    if (Button_Name.IsEmpty() )
        Button_Name = FText::FromName(names[Widget_Index]);  // Set Name | Default Buttons
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Update_State() const
{
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();

        if (!user_settings != 0)
        return;

    switch (Option_Type)
    {
    case EOption_Type::EPT_None:
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
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Setting_Button::Button_Redraw_Implementation()
{
    int yy = 0;  // Called if not released in BP
}
//------------------------------------------------------------------------------------------------------------




// UAMenu_Main_Settings
void UAMenu_Main_Settings::NativeConstruct()
{
	Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Func(float test)
{
    UGameUserSettings *user_settings;

    user_settings = GEngine->GetGameUserSettings();
    Spin_Box_Root->SetValue(test);

    if (Button_Type == EOption_Type::EPT_Frame_Rate)
        user_settings->SetFrameRateLimit(test);
    if (Button_Type == EOption_Type::EPT_Screen_Percentage)
        user_settings->SetResolutionScaleNormalized(test);

    user_settings->ApplySettings(false);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Button_Array_Emplace(const int button_index, UWidget *button_widget)
{
    Button_Array[button_index] = button_widget;
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Button_Active_Draw()
{
    int button_index = 0;
    double temp = 0.0;
    UGameUserSettings *user_settings;
    UAMenu_Main_Setting_Button *menu_main_setting_button;

    user_settings = GEngine->GetGameUserSettings();
    if (!user_settings != 0)
    return;

    switch (Button_Type)
    {
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
    case EOption_Type::EPT_Frame_Rate:  // !!!
        temp = user_settings->GetFrameRateLimit();
        Spin_Box_Root->SetValue(temp);
        return;
        break;
    case EOption_Type::EPT_Screen_Resolution:
        //button_index = user_settings->GetDefaultWindowMode();
        break;
    case EOption_Type::EPT_Screen_Percentage:
        //button_index = user_settings->GetDefaultWindowMode();
        break;
    case EOption_Type::EPT_Toogle_Directx:
        //button_index = user_settings->GetDefaultWindowMode();
        break;
    case EOption_Type::EPT_Show_Frame_Per_Sec:
        //button_index = user_settings->GetDefaultWindowMode();
        break;
    default:
        button_index = 0;
        break;
    }
    if (button_index > 5 || button_index < 0)
        button_index = 0;
    
    menu_main_setting_button = Cast<UAMenu_Main_Setting_Button>(Button_Array[button_index] );
    menu_main_setting_button->Button_Redraw();
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
        Spin_Box_Root->SetValue(user_settings->GetFrameRateLimit());
    if (Button_Type == EOption_Type::EPT_Screen_Percentage)
        Spin_Box_Root->SetValue(user_settings->GetResolutionScaleNormalized() );

    Spin_Box_Root->OnValueChanged.AddDynamic(this, &UAMenu_Main_Settings::Func);
}
//------------------------------------------------------------------------------------------------------------




// AJamScream_Game_Mode
AJamScream_Game_Mode::AJamScream_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------
