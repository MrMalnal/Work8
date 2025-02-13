#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BlindItem.generated.h"

class UImage;

UCLASS()
class SPARTA_CPP_API ABlindItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ABlindItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Delay;

	virtual void ActivateItem(AActor* Activator) override;

	FTimerHandle HideImageTimerHandle;

	void BlindForDuration();
};
