// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"

#include "CustomerMarker.h"
#include "Components/SphereComponent.h"
#include "GroupProj27/GameLevelMode.h"
#include "GroupProj27/ComponentClasses/PizzaComponent.h"
#include "GroupProj27/Interfaces/ParkourPlayerInterface.h"
#include "GroupProj27/Subsystems/CalenderSubsystem.h"
#include "GroupProj27/Subsystems/ClockSubsystem.h"
#include "GroupProj27/Subsystems/CustomerSubsystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AShop::AShop()
{
	mShopMesh = CreateDefaultSubobject<UStaticMeshComponent>("Shop Mesh");
	mShopMesh->SetupAttachment(RootComponent);

	mCountdownCollider = CreateDefaultSubobject<USphereComponent>("CountdownCollider");
	mNormalCollider = CreateDefaultSubobject<USphereComponent>("NormalCollider");

	mCountdownCollider->SetupAttachment(mShopMesh);
	mNormalCollider->SetupAttachment(mShopMesh);

	mPizzaComp = CreateDefaultSubobject<UPizzaComponent>("PizzaComp");
}

void AShop::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AShop::Init()
{
	mCountdownCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCountdownColliderOverlapBegin);
	mNormalCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnNormalColliderOverlapBegin);

	const auto Instance = GetGameInstance();
	UCustomerSubsystem *CustomerSubs = Instance->GetSubsystem<UCustomerSubsystem>();
	UClockSubsystem *ClockSubs = Instance->GetSubsystem<UClockSubsystem>();
	AGameLevelMode *GameMode = Cast<AGameLevelMode>(GetWorld()->GetAuthGameMode());
		
	if(CustomerSubs)
	{
		CustomerSubs->OnOrderCollected.AddDynamic(this, &ThisClass::OnOrderCollected);
	}
	if(ClockSubs)
	{
		ClockSubs->FinishTimer.AddDynamic(this, &ThisClass::OnTimerFinished);
	}
	if(GameMode)
	{
		GameMode->OnDecisionMade.AddDynamic(this, &ThisClass::OnDecisionMade);
	}

	ToggleCollider(NormalCollider);

	ToggleShop(true);
}


void AShop::OnCountdownColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UParkourPlayerInterface::StaticClass()))
	{
		const auto CustomerSubs = GetGameInstance()->GetSubsystem<UCustomerSubsystem>();

		if(CustomerSubs)
		{
			AverageOrderQuality = CalculateAverage();
			CustomerSubs->OnChefReviewGenerated.Broadcast(AverageOrderQuality);
			AverageOrderQuality = 0;
		}

		if(const auto ClockSubs = GetGameInstance()->GetSubsystem<UClockSubsystem>())
		{
			switch (ClockSubs->GetClockStatus()) {
			case TIMER_IDLE:

				break;
			case TIMER_RUNNING:
				ClockSubs->StopTimer.Broadcast();
				MakeOrders(OtherActor);
				break;
			case TIMER_INTERRUPTED:

				break;
			case TIMER_FINISHED:
				UpdateEntities(OtherActor);
				CustomerSubs->OnOrderInitialised.Broadcast();
				break;
			}
		}
	}
}

void AShop::OnNormalColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UParkourPlayerInterface::StaticClass()))
	{
		if(const auto CustomerSubs = GetGameInstance()->GetSubsystem<UCustomerSubsystem>())
		{
			if(!CustomerSubs->HasOrders())
				MakeOrders(OtherActor);
		}
	}
}

void AShop::OnOrderCollected(FString ID, int RemainingOrders)
{
	if(const auto CustomerSubs = GetGameInstance()->GetSubsystem<UCustomerSubsystem>())
	{
		const auto details = CustomerSubs->GetOrderStatus(ID)->GetDetails();
		if(RemainingOrders <=0)
		{
			if(const UClockSubsystem *ClockSubs = GetGameInstance()->GetSubsystem<UClockSubsystem>())
			{
				ClockSubs->StartTimer.Broadcast();
			}
			ToggleShop(true);
			ToggleCollider(CountdownCollider);
		}
		else
		{
			AverageOrderQuality += (details.Quality <=0)? 0: details.Quality;
		}
	}
}

void AShop::OnDecisionMade_Implementation(EGameDecision Decision)
{
}

void AShop::OnTimerFinished()
{
	MakeOrders(nullptr);
}

void AShop::MakeOrders(AActor* PlayerRef)
{
	if(!PlayerRef)
	{
		mPizzaComp->InitiateOrders(false);
	}
	else
	{
		mPizzaComp->InitiateOrders(true);

		UpdateEntities(PlayerRef);
	}
	
	mPizzaComp->StartQualityTimer();
	
	if(const auto CalenderSubs = GetGameInstance()->GetSubsystem<UCalenderSubsystem>())
	{
		CalenderSubs->StartDay();
	}
}

void AShop::ToggleCollider(EColliderToggle ColliderToToggle)
{
	switch (ColliderToToggle)
	{
	case CountdownCollider:
		
		mNormalCollider->SetGenerateOverlapEvents(false);
		mNormalCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		mCountdownCollider->SetGenerateOverlapEvents(true);
		mCountdownCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	case NormalCollider:
		mNormalCollider->SetGenerateOverlapEvents(true);
		mCountdownCollider->SetGenerateOverlapEvents(false);

		mNormalCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		mCountdownCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case NoCollider:
		mNormalCollider->SetGenerateOverlapEvents(false);
		mCountdownCollider->SetGenerateOverlapEvents(false);

		mNormalCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		mCountdownCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case BothCollider:
		mNormalCollider->SetGenerateOverlapEvents(true);
		mCountdownCollider->SetGenerateOverlapEvents(true);
		
		mNormalCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		mCountdownCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	}
}

void AShop::UpdateEntities(AActor* target)
{
	IParkourPlayerInterface::Execute_OnOrdersRequested(target);

	ToggleShop(false);
}

int AShop::CalculateAverage()
{
	return UKismetMathLibrary::FCeil(AverageOrderQuality/mPizzaComp->TotalOrders);
}
