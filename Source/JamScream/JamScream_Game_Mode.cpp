#include "JamScream_Game_Mode.h"

#include "Misc/ConfigCacheIni.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

// UJamScreen_Widget
void UJamScreen_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UJamScreen_Widget::Update_Options() const
{
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();

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
        user_settings->SetFrameRateLimit(24);
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
void UJamScreen_Widget::Toogle_DirectX() const
{
    FString config_path = FPaths::ProjectConfigDir() + TEXT("DefaultEngine.ini");
    FString current_rhi;

    if (GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), current_rhi, config_path) )  // Get current DXT
        if (current_rhi == TEXT("DefaultGraphicsRHI_DX12") )  // Toogle DX
            GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), TEXT("DefaultGraphicsRHI_DX11"), config_path);
        else
            GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), TEXT("DefaultGraphicsRHI_DX12"), config_path);

    GConfig->Flush(false, config_path);  // Save to config
    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("quit"));  // Exit from game
}
//------------------------------------------------------------------------------------------------------------
void UJamScreen_Widget::Set_Screen_Percentage() const
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

    user_settings->ApplySettings(false);
    user_settings->SaveSettings();
}
//------------------------------------------------------------------------------------------------------------
void UJamScreen_Widget::Set_Screen_Resolution() const
{
    FIntPoint point;
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
    user_settings->ApplySettings(false);
}
//------------------------------------------------------------------------------------------------------------




// AJamScream_Game_Mode
AJamScream_Game_Mode::AJamScream_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------

