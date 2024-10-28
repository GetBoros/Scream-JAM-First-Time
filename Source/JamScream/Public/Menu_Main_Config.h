#pragma once

// Menu_Main_Config
class JAMSCREAM_API Menu_Main_Config
{
public:
    ~Menu_Main_Config();
    Menu_Main_Config();

    static constexpr int Button_Setting_Count = 5;
    static constexpr int Screen_Resolution_Array_Size = 5;
    static const FIntPoint Screen_Resolution_Array[Screen_Resolution_Array_Size];
    static const FName Button_Name_Defaults[Button_Setting_Count];

    static constexpr FLinearColor Button_Active = FLinearColor(0.017642f, 0.026241f, 0.056128f);
    static constexpr FLinearColor Button_Inactive = FLinearColor(0.066626f, 0.341915f, 0.887923f);
};
//-----------------------------------------------------------------------------------------------------------
