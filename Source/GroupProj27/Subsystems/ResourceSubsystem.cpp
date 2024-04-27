#include "ResourceSubsystem.h"

void UResourceSubsystem::Deinitialize()
{
	OnBalanceUpdate.Clear();
	Super::Deinitialize();
}

void UResourceSubsystem::AddBalance(int increaseBy)
{
	mCurrentResource += increaseBy;
	OnBalanceUpdate.Broadcast(mCurrentResource);
}

void UResourceSubsystem::DeductBalance(int decreaseBy)
{
	mCurrentResource -= decreaseBy;
	OnBalanceUpdate.Broadcast(mCurrentResource);
}