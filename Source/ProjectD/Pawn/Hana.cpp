#include "Pawn/Hana.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h" // 추가!

AHana::AHana()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHana::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            SubSystem->AddMappingContext(DefaultMappingContext, 0);
            UE_LOG(LogTemp, Display, TEXT("Begin play in hana Character"));
            UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext: %s"), DefaultMappingContext ? TEXT("Valid") : TEXT("NULL"));
        }
    }
}

void AHana::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHana::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(
            IA_Move,
            ETriggerEvent::Triggered,
            this,
            &AHana::HandleMove
        );

        UE_LOG(LogTemp, Display, TEXT("Bind Action"));
    }
}

void AHana::HandleMove(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    UE_LOG(LogTemp, Display, TEXT("IA_Move input value: %s"), *MovementVector.ToString());
}
