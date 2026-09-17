// Copyright Druid Mechanics


#include "AbilitySystem/Data/LootTiers.h"
// 每种掉落物独立重复 MaxNumberToSpawn 次，每次按 `ChanceToSpawn` 百分比掷骰决定是否产出
TArray<FLootItem> ULootTiers::GetLootItems()
{
	TArray<FLootItem> ReturnItems;

	for (FLootItem& Item : LootItems)
	{
		for (int32 i = 0; i < Item.MaxNumberToSpawn; ++i)
		{
			if (FMath::FRandRange(1.f, 100.f) < Item.ChanceToSpawn)
			{
				FLootItem NewItem;
				NewItem.LootClass = Item.LootClass;
				NewItem.bLootLevelOverride = Item.bLootLevelOverride;
				ReturnItems.Add(NewItem);
			}
		}
	}

	return ReturnItems;
}
