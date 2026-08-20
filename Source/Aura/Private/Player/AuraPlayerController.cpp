// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Input/AuraInputComponent.h"


AAuraPlayerController::AAuraPlayerController()
{
	
	bReplicates=true;
	//样条线初始化
	Spline=CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//光标追踪
	CursorTrace();
	
	AutoRun();
	/*有关鼠标点击移动的 开始*/
	
	/*有关鼠标点击移动的 结束*/
	
}

void AAuraPlayerController::InitializeSubsystem()
{
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAuraPlayerController::InitializeSubsystem,1, false);
	check(AureContext);
	//这个是换了一下
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ULocalPlayer* LocalPlayer = PlayerController ? Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()) : nullptr;
	//
	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(AureContext,0);

	
	bShowMouseCursor=true;
	
	//这杨鼠标就不会所在视口里了
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//这个好像是当鼠标离开视口时不隐藏
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAuraInputComponent*AuraInputComponent=CastChecked<UAuraInputComponent>(InputComponent);
	
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	//做两个处理 按下 和松开
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Started,this,&AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Completed,this,&AAuraPlayerController::ShiftReleased);
	
	
	AuraInputComponent->BindAbilityInputActions(InputConfig,this,&AAuraPlayerController::AbilityInputTagPagPressed,&AAuraPlayerController::AbilityInputTagReleased,&AAuraPlayerController::AbilityInputTagHeld);
}

void AAuraPlayerController::ShiftPressed()
{
	bShiftPressed=true;
}

void AAuraPlayerController::ShiftReleased()
{
	bShiftPressed=false;
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	
	FRotator Rotation=GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	
	//获取前方向的旋转
	FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	//应该是移动
	if (APawn*ControlledPawn=GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	if (!CursorHitResult.bBlockingHit)return;
	
	LastActor=ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursorHitResult.GetActor());
	
	/*
	 * 这个注释会说明从光标进行线性跟踪的几种情况
	 * A. LastActor 和 ThisActor 都为空
	 *      什么都不做
	 * B. LastActor 为空 ThisActor不为空
	 *      显示高亮
	 * C. LastActor不为空 ThisActor为空
	 *      取消高亮
	 * D.LastActor 和 ThisActor 都不为空 但不相等
	 *     LastActor取消高亮  ThisActor显示高亮
	 * E.LastActor 和 ThisActor 都不为空 且相等
	 *     什么都不做
	 */
	
	if (LastActor==nullptr)
	{
		if (ThisActor!=nullptr)
		{
			//B情况
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor!=nullptr)
		{
			if (LastActor!=ThisActor)
			{
				//D情况
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
				
			}
		}
		else
		{
			//C情况
			LastActor->UnHighlightActor();
		}
	}
	
}

void AAuraPlayerController::AbilityInputTagPagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		//三元运算符表达式
		bTargeting= ThisActor ? true:false;
		//刚点击 不确定是否是长按或者短按
		bAutoRunning=false;
	}
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//当不是左键点击时
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	
	//这个是 是否瞄准
	if(!bTargeting&&!bShiftPressed)
	{
		APawn *AuraPawn = GetPawn();
		if(AuraPawn && FollowTime<=ShortPressTime)
		{
			//当时点按是生成样条线 按照样条线移动
			UNavigationPath* NavPath= UNavigationSystemV1::FindPathToLocationSynchronously(this,AuraPawn->GetActorLocation(),CachedDestination);
			if(NavPath)
			{
				Spline->ClearSplinePoints();
				for (auto Pointloc:NavPath->PathPoints)
				{
					Spline->AddSplinePoint(Pointloc,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),Pointloc,50,8,FColor::Green,false,8);
				}
				CachedDestination=NavPath->PathPoints[NavPath->PathPoints.Num()-1];
				bAutoRunning=true;
			}
			
		}
		FollowTime=0.f;
	}
	else
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
			
		}
	}
	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//当不是左键点击时
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	//这个是 是否瞄准
	if(bTargeting||bShiftPressed)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
			
		}
	}
	//这个才是移动的逻辑
	else
	{
		//累计时间
		FollowTime+=GetWorld()->GetDeltaSeconds();
		
		//获取命中的信息
		if (CursorHitResult.bBlockingHit)
		{
			//赋值
			CachedDestination=CursorHitResult.Location;
		}
		
		if (FollowTime>ShortPressTime)
		{
			/*按住左键鼠标按键时，获取世界中的目标位置（也就是要移动的位置）*/
			//命中目标
			
			
			GetPawn()->AddMovementInput((CachedDestination-GetPawn()->GetActorLocation()).GetSafeNormal());
			
		}
	}
	
	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	//赋值
	if (AuraAbilitySystemComponent==nullptr)
	{
		//获取能力系统组件
		AuraAbilitySystemComponent=Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::AutoRun()
{
	if (!HasAuthority())
	{
		
	}
	if (!bAutoRunning)return;
	APawn *AuraPawn = GetPawn();
	if (AuraPawn)
	{
		//沿着样条曲线 Spline 组件，查找距离玩家角色世界坐标最近的曲线上点
		FVector LocationOnSpline=Spline->FindLocationClosestToWorldLocation(AuraPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		//根据传入的世界坐标点，获取样条曲线此处的前进切线方向向量
		FVector Direction=Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		
		AuraPawn->AddMovementInput(Direction);
		
		//需要检查与目标的距离 判断是否在自动移动接受半径内
		float DistanceToDestination=(LocationOnSpline-CachedDestination).Length();
		if (DistanceToDestination<=AutoRunAcceptanceRadius)
		{
			bAutoRunning=false;
		}
	}
}





