#pragma once

#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "JamScream_Character.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

// AJamScreamCharacter
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
//------------------------------------------------------------------------------------------------------------
UCLASS(config=Game) class AJamScream_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AJamScream_Character();

	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(class UInputComponent *player_input_component);

	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Camera) USpringArmComponent *Spring_Arm_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Camera) UCameraComponent *Camera_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Input) UInputMappingContext *Default_Mapping_Context;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Input) UInputAction *Action_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Input) UInputAction *Action_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Input) UInputAction *Action_Look;
};
//------------------------------------------------------------------------------------------------------------
