// Copyright Druid Mechanics


#include "AI/BTTask_Attack.h"
// 调用父类 ExecuteTask；任务触发攻击动作（无复杂本地算法）
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
