#include "DiceCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"

ADiceCharacter::ADiceCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADiceCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ADiceCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADiceCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 1. Active le Mapping Context
    if (APlayerController* PlayerController =
        Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer()))
        {
            if (PlayerMappingContext)
            {
                Subsystem->AddMappingContext(PlayerMappingContext, 0);
            }
        }
    }

    // 2. Relie IA_Move à la fonction Move()
    if (UEnhancedInputComponent* EnhancedInputComponent =
        Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(
                MoveAction,
                ETriggerEvent::Triggered,
                this,
                &ADiceCharacter::Move
            );
        }
    }
}

void ADiceCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    AddMovementInput(
        GetActorForwardVector(),
        MovementVector.Y
    );

    AddMovementInput(
        GetActorRightVector(),
        MovementVector.X
    );
}