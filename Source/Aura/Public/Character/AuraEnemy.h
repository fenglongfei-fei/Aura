//LF

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"      // Must be the last include

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();

	// Implement interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;


	/*UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;*/



};
