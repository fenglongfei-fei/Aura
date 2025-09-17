// LF

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/AuraEnemy.h"
#include "AuraPlayerController.generated.h"


class   IEnemyInterface;
class 	UInputMappingContext;
class   UInputAction;
struct  FInputActionValue;


/**
 *
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")

	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);


	void CursorTrace();

	// ½Ó¿ÚÖ¸Õëproblem
	/*TObjectPtr<IEnemyInterface> LastActor;
	TObjectPtr<IEnemyInterface> ThisActor;*/

	/*AActor* LastActor;
	AActor* ThisActor;*/

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
		
};
