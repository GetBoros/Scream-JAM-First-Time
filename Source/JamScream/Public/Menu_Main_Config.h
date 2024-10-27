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
};
//-----------------------------------------------------------------------------------------------------------
