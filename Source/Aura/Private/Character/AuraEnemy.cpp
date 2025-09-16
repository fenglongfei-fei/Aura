// LF


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

}

// 突出显示
void AAuraEnemy::HighlightActor()
{
	//bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); 
	weapon->SetRenderCustomDepth(true);
	weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

// 不突出显示
void AAuraEnemy::UnHighlightActor()
{
	//bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(false);
	weapon->SetRenderCustomDepth(false);

}
