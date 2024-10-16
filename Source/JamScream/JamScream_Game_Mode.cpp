#include "JamScream_Game_Mode.h"
#include "JamScream_Character.h"
#include "UObject/ConstructorHelpers.h"

// AJamScream_Game_Mode
AJamScream_Game_Mode::AJamScream_Game_Mode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter") );
	if (PlayerPawnBPClass.Class != 0)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}
//------------------------------------------------------------------------------------------------------------
