// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerMarker.h"

#include "Components/SphereComponent.h"
#include "GroupProj27/HelperClasses/EnumClass.h"
#include "GroupProj27/Interfaces/ParkourPlayerInterface.h"
#include "GroupProj27/Subsystems/CustomerSubsystem.h"
#include "GroupProj27/Subsystems/ResourceSubsystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ACustomerMarker::ACustomerMarker()
{
	mCollider = CreateDefaultSubobject<USphereComponent>("Collider");
	mCollider->SetupAttachment(RootComponent);
}

void ACustomerMarker::BeginPlay()
{
	Super::BeginPlay();
	CustomerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCustomerSubsystem>();
	mCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnColliderOverlapBegin);

	if(CustomerSubsystem)
	{
		ID = CustomerSubsystem->RegisterCustomer(this);
	}
}

void ACustomerMarker::BeginDestroy()
{
	OnPizzaUpdated.RemoveAll(this);
	Super::BeginDestroy();
}

void ACustomerMarker::OnColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UParkourPlayerInterface::StaticClass()) && bIsActivated)
	{
		CollectPizza();
	}
}

void ACustomerMarker::ToggleCustomer_Implementation(bool Value)
{
	bChosenForOrderList = false;
	CustomerSubsystem->OnOrderInitialised.RemoveAll(this);
}

void ACustomerMarker::CollectPizza_Implementation()
{
	ToggleCustomer(false);
	
	CustomerSubsystem->OrderCollected(ID);
	
	if(const auto resourceSubs = GetGameInstance()->GetSubsystem<UResourceSubsystem>())
	{
		if (QualityRange.Contains(PizzaDetails.QualityType))
		{
			// Directly get the range without creating a temporary object
			FMinMaxStruct range = QualityRange[PizzaDetails.QualityType];
			const int randResource = UKismetMathLibrary::RandomIntegerInRange(range.min, range.max);
			resourceSubs->AddBalance(randResource);
		}
	}
}

void ACustomerMarker::OnInitialisedForOrder()
{
	if(bChosenForOrderList)
	{
		ToggleCustomer(true);
		CustomerSubsystem->OnOrderInitialised.RemoveAll(this);
	}
}

void ACustomerMarker::Init(FPizzaStruct pDetails)
{
	PizzaDetails = pDetails;
	DecreaseRate = pDetails.DecreaseRate;
	bChosenForOrderList = true;
	CustomerSubsystem->OnOrderInitialised.AddDynamic(this, &ThisClass::OnInitialisedForOrder);
}

void ACustomerMarker::UpdatePizza()
{
	FString &review = PizzaDetails.Review;
	TEnumAsByte<EPizzaQuality> &qualityType = PizzaDetails.QualityType;
	const int &CurrentQuality = PizzaDetails.Quality;

	// Update the Current Quality
	DeductQuality(DecreaseRate);

	// Update the Current Review
	if(CurrentQuality >= 70)
	{
		qualityType = Best;
		review = "Perfect!!";
	}
	else if(CurrentQuality >= 40 && CurrentQuality <70)
	{
		qualityType = Good;
		review = "Good!!";
	}
	else if(CurrentQuality >= 10 && CurrentQuality <40)
	{
		qualityType = Average;
		review = "Average!!";
	}
	else
	{
		qualityType = Poor;
		review = "POOP!!!";
	}
	OnPizzaUpdated.Broadcast(PizzaDetails);
}

// Quality Manipulation
void ACustomerMarker::AddQuality_Implementation(int increaseBy)
{
	int &CurrentQuality = PizzaDetails.Quality;
	CurrentQuality += increaseBy;

	OnPizzaUpdated.Broadcast(PizzaDetails);
}

void ACustomerMarker::DeductQuality_Implementation(int decreaseBy)
{
	int &CurrentQuality = PizzaDetails.Quality;

	CurrentQuality-= decreaseBy;
	OnPizzaUpdated.Broadcast(PizzaDetails);

}