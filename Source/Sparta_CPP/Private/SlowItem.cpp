#include "SlowItem.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"

ASlowItem::ASlowItem()
{
	Duration = 3.0f;
}

void ASlowItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (ASpartaPlayerController* SpartaPlayerController = GetWorld()->GetFirstPlayerController<ASpartaPlayerController>())
	{
		if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(SpartaPlayerController->GetCharacter()))
		{
			float CurrentNormalSpeed = SpartaCharacter->GetNormalSpeed();
			float CurrentSprintSpeed = SpartaCharacter->GetSprintSpeed();

			SpartaCharacter->SetNormalSpeed(CurrentNormalSpeed * 0.5);
			SpartaCharacter->SetSprintSpeed(CurrentSprintSpeed * 0.5);

			FTimerHandle MoveTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				MoveTimerHandle,
				[CurrentNormalSpeed, CurrentSprintSpeed, SpartaCharacter]()
				{
					if (SpartaCharacter)
					{
						SpartaCharacter->SetNormalSpeed(CurrentNormalSpeed);
						SpartaCharacter->SetSprintSpeed(CurrentSprintSpeed);
					}
				},
				5.0f,
				false
			);
		}
	}
	DestroyItem();
}