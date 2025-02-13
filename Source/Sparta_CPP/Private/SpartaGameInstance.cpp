#include "SpartaGameInstance.h"

USpartaGameInstance::USpartaGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
	CurrentWave = 1;
	ItemToSpawn = 40;
}

void USpartaGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
}