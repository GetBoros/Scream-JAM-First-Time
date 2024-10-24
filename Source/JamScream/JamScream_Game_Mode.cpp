#include "JamScream_Game_Mode.h"

#include "Misc/ConfigCacheIni.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

// UAMenu_Main_Settings
void UAMenu_Main_Settings::NativeConstruct()
{
	Super::NativeConstruct();

    User_Settings = GEngine->GetGameUserSettings();
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Toogle_DirectX() const
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
void UAMenu_Main_Settings::Set_Screen_Percentage() const
{
    if (!User_Settings != 0)
        return;

    switch (Widget_Index)
    {
    case 0:
        User_Settings->SetResolutionScaleValueEx(50);
        break;
    case 1:
        User_Settings->SetResolutionScaleValueEx(75);
        break;
    case 2:
        User_Settings->SetResolutionScaleValueEx(100);
        break;
    default:
        User_Settings->SetResolutionScaleValueEx(50);
        break;
    }
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Set_Screen_Resolution() const
{
    FIntPoint point {};
    
    if (!User_Settings != 0)
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
    User_Settings->SetScreenResolution(point);
    User_Settings->SetFullscreenMode(EWindowMode::Fullscreen);
}
//------------------------------------------------------------------------------------------------------------
void UAMenu_Main_Settings::Update_Options() const
{
    if (!User_Settings != 0)
        return;

    switch (Option_Type)
    {
    case EOption_Type::EPT_None:
        break;
    case EOption_Type::EPT_Window_Mode:
        User_Settings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(Widget_Index) );
        User_Settings->ApplyResolutionSettings(false);
        break;
    case EOption_Type::EPT_Quality_Presset:
        User_Settings->SetOverallScalabilityLevel(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Shadows:
        User_Settings->SetShadowQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Foliage:
        User_Settings->SetFoliageQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Texture:
        User_Settings->SetTextureQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Shading:
        User_Settings->SetShadingQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Reflection:
        User_Settings->SetReflectionQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Anti_Aliasing:
        User_Settings->SetAntiAliasingQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Visual_Effects:
        User_Settings->SetVisualEffectQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_View_Distances:
        User_Settings->SetViewDistanceQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Post_Processing:
        User_Settings->SetPostProcessingQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Quality_Global_Illumination_Quality:
        User_Settings->SetGlobalIlluminationQuality(Widget_Index);
        break;
    case EOption_Type::EPT_Frame_Rate:
        User_Settings->SetFrameRateLimit(24);
        break;
    case EOption_Type::EPT_Screen_Resolution:
        Set_Screen_Resolution();
        break;
    case EOption_Type::EPT_Screen_Percentage:
        //Set_Screen_Percentage();
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
    User_Settings->ApplySettings(false);
}
//------------------------------------------------------------------------------------------------------------




// AJamScream_Game_Mode
AJamScream_Game_Mode::AJamScream_Game_Mode()
{
}
//------------------------------------------------------------------------------------------------------------

