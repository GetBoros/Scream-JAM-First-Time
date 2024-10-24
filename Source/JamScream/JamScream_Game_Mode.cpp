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
void UJamScreen_Widget::Toogle_DirectX()
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
void UJamScreen_Widget::Set_Screen_Percentage(const int button_index)
{
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();

    if (!user_settings != 0)
        return;

    switch (button_index)
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
void UJamScreen_Widget::Set_Screen_Resolution(const int button_index)
{
    FIntPoint point;
    UGameUserSettings *user_settings = GEngine->GetGameUserSettings();

    if (!user_settings != 0)
        return;

    switch (button_index)
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

