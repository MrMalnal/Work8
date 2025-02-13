#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowItem.generated.h"

UCLASS()
class SPARTA_CPP_API ASlowItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ASlowItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Duration;

	virtual void ActivateItem(AActor* Activator) override;
};
