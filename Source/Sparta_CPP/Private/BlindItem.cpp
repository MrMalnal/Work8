#include "BlindItem.h"
#include "SpartaGameState.h"
#include "SpartaPlayerController.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"

ABlindItem::ABlindItem()
{
	Delay = 3.0f;
}

void ABlindItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (Activator && Activator->ActorHasTag("Player"))
	{
		BlindForDuration();
		DestroyItem();
	}
}

void ABlindItem::BlindForDuration()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				UImage* Image1 = Cast<UImage>(HUDWidget->GetWidgetFromName(TEXT("Blind1")));
				UImage* Image2 = Cast<UImage>(HUDWidget->GetWidgetFromName(TEXT("Blind2")));
				UImage* Image3 = Cast<UImage>(HUDWidget->GetWidgetFromName(TEXT("Blind3")));

				if (Image1) Image1->SetVisibility(ESlateVisibility::Visible);
				if (Image2) Image2->SetVisibility(ESlateVisibility::Visible);
				if (Image3) Image3->SetVisibility(ESlateVisibility::Visible);

				GetWorld()->GetTimerManager().SetTimer(
					HideImageTimerHandle,
					[Image1, Image2, Image3]()
					{
						if (Image1) Image1->SetVisibility(ESlateVisibility::Collapsed);
						if (Image2) Image2->SetVisibility(ESlateVisibility::Collapsed);
						if (Image3) Image3->SetVisibility(ESlateVisibility::Collapsed);
					},
					Delay,
					false
				);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("HUDWidget is nullptr"));
			}
		}
	}
}