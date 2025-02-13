#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "SpartaGameInstance.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTables.SetNum(3);
}

AActor* ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (ItemDataTables.IsEmpty()) return nullptr;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			const int& Wave = SpartaGameInstance->CurrentWave;
			TArray<FItemSpawnRow*> AllRows;
			static const FString ContextString(TEXT("ItemSpawnContext"));
			ItemDataTables[Wave - 1]->GetAllRows(ContextString, AllRows);

			if (AllRows.IsEmpty()) return nullptr;

			float TotalChance = 0.0f;
			for (const FItemSpawnRow* Row : AllRows)
			{
				if (Row)
				{
					TotalChance += Row->SpawnChance;
				}
			}

			const float RandValue = FMath::FRandRange(0.0f, TotalChance);
			float AccumulateChance = 0.0f;
			for (FItemSpawnRow* Row : AllRows)
			{
				AccumulateChance += Row->SpawnChance;
				if (RandValue <= AccumulateChance)
				{
					return Row;
				}
			}
		}
	}

	return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return nullptr;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
	return SpawnedActor;
}