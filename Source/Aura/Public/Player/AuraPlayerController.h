// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"


class IHighlightInterface;
class UNiagaraSystem;
class UDamageTextComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;
class AMagicCircle;

/** 光标目标识别状态 */
enum class ETargetingStatus : uint8
{
	/// 当前指向敌人
	TargetingEnemy,
	/// 当前指向非敌人（可交互对象等）
	TargetingNonEnemy,
	/// 当前未指向任何目标（地面移动等）
	NotTargeting
};

/**
 * AAuraPlayerController
 *
 * 自定义玩家控制器，负责：
 * - 处理输入绑定（Enhanced Input）
 * - 光标检测与高亮（Highlight Interface）交互
 * - 自动寻路（AutoRun）和点击特效播放
 * - 显示伤害浮字与法术圈（MagicCircle）
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	/** 每帧调用（覆盖以进行光标追踪、自动跑动、法术圈更新） */
	virtual void PlayerTick(float DeltaTime) override;

	/** 客户端 RPC：在目标处显示伤害数字（可靠） */
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);

	/** 在玩家位置显示法术圈（可指定 Decal 材质） */
	UFUNCTION(BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial = nullptr);

	/** 隐藏法术圈实例 */
	UFUNCTION(BlueprintCallable)
	void HideMagicCircle();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	/** Enhanced Input 映射上下文（编辑器可指定） */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	/** 移动动作 */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	/** Shift 键动作（用于切换行为，例如保持跟随） */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	/** Shift 键按下回调（内联） */
	void ShiftPressed() { bShiftKeyDown = true; };
	/** Shift 键释放回调（内联） */
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;

	/** Enhanced Input 的移动回调处理 */
	void Move(const FInputActionValue& InputActionValue);

	/** 光标射线检测与高亮管理 */
	void CursorTrace();
	TObjectPtr<AActor> LastActor;
	TObjectPtr<AActor> ThisActor;
	FHitResult CursorHit;
	static void HighlightActor(AActor* InActor);
	static void UnHighlightActor(AActor* InActor);

	/** 能力输入标签的按下/释放/按住回调（转发到 ASC） */
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	/** 输入配置数据（Ability 与 InputTag 对应关系） */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	/** 缓存的 AuraAbilitySystemComponent 指针（懒取） */
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	/** 自动寻路相关字段 */
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	ETargetingStatus TargetingStatus = ETargetingStatus::NotTargeting;

	/** 自动跑步接受半径（到达目标视为结束） */
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	/** 用于在客户端构造路径曲线以驱动移动的 SplineComponent（本地可视化/播放路径） */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	/** 点击时播放的粒子特效（Niagara） */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ClickNiagaraSystem;

	/** 执行自动跑动的内部方法 */
	void AutoRun();

	/** 用于显示目标上方伤害文字的组件类（蓝图/编辑器配置） */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	/** 法术圈 Actor 的类，用于在客户端生成和控制 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMagicCircle> MagicCircleClass;

	/** 当前生成的法术圈实例（仅客户端） */
	UPROPERTY()
	TObjectPtr<AMagicCircle> MagicCircle;

	/** 更新法术圈位置（跟随光标） */
	void UpdateMagicCircleLocation();
};
