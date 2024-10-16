#include "JamScream_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// AJamScream_Character
AJamScream_Character::AJamScream_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0, 96.0);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;  // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);  // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.0;
	GetCharacterMovement()->AirControl = 0.35;
	GetCharacterMovement()->MaxWalkSpeed = 500.0;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0;

	Spring_Arm_Component = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring_Arm_Component") );
	Spring_Arm_Component->SetupAttachment(RootComponent);
	Spring_Arm_Component->TargetArmLength = 400.0; // The camera follows at this distance behind the character	
	Spring_Arm_Component->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_Component") );
	Camera_Component->SetupAttachment(Spring_Arm_Component, USpringArmComponent::SocketName);  // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera_Component->bUsePawnControlRotation = false;  // Camera does not rotate relative to arm
}
//------------------------------------------------------------------------------------------------------------
void AJamScream_Character::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AJamScream_Character::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	if (APlayerController *player_controller = Cast<APlayerController>(GetController() ) )
	{
		if (UEnhancedInputLocalPlayerSubsystem *subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer() ) )
			subsystem->AddMappingContext(Default_Mapping_Context, 0);
	}
	
	if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(player_input_component) )
	{
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		enhanced_input_component->BindAction(Action_Move, ETriggerEvent::Triggered, this, &AJamScream_Character::Move);
		enhanced_input_component->BindAction(Action_Look, ETriggerEvent::Triggered, this, &AJamScream_Character::Look);
	}
	else
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
}
//------------------------------------------------------------------------------------------------------------
void AJamScream_Character::Move(const FInputActionValue &value)
{
	FVector2D MovementVector = value.Get<FVector2D>();  // input is a Vector2D

	if (Controller != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);  // find out which way is forward
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);  // get forward vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);  // get right vector 

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
//------------------------------------------------------------------------------------------------------------
void AJamScream_Character::Look(const FInputActionValue &value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != 0)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//------------------------------------------------------------------------------------------------------------
