#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // 추가!
#include "Hana.generated.h"

UCLASS()
class PROJECTD_API AHana : public ACharacter
{
    GENERATED_BODY()

public:
    AHana();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void HandleMove(const FInputActionValue& Value);

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* IA_Move;
};


//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_Look;
//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_Jump;
//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_Charge;
//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_Hit;
//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_Grab;
//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_ChangeAttackMode;
//UPROPERTY(EditDefaultsOnly, Category = "Input")
//class UInputAction* IA_Crouch;
