#include "ResourceSubsystem.h"

void UResourceSubsystem::Deinitialize()
{
	OnBalanceUpdate.Clear();
	Super::Deinitialize();
}

int UResourceSubsystem::AddBalance(int increaseBy)
{
	mCurrentResource += increaseBy;
	OnBalanceUpdate.Broadcast(mCurrentResource);
	return mCurrentResource;
}

int UResourceSubsystem::DeductBalance(int decreaseBy)
{
	mCurrentResource -= decreaseBy;
	OnBalanceUpdate.Broadcast(mCurrentResource);
	return mCurrentResource;
}