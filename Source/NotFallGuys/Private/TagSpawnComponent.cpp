#include "TagSpawnComponent.h"
#include "TagCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

UTagSpawnComponent::UTagSpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTagSpawnComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTagSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTagSpawnComponent::CheckToSpawnCharacter(APlayerController* playerController) const
{
	APawn* newPawn = SpawnCharacter();
	if (!newPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn character failed"));
		return;
	}
	
	if (!playerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is null. Bot has benn spawned"));
		return;
	}
	playerController->Possess(newPawn);
	IToggleInputInterface* inputInterface = Cast<IToggleInputInterface>(newPawn);
	if(!inputInterface) return;
	inputInterface->SetInputState(false);
}

APawn* UTagSpawnComponent::SpawnCharacter() const
{
	if (GetCharacterToSpawn() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldnt get character to spawn"));
		return nullptr;
	}

	FTransform startingTransform = FTransform::Identity;
	startingTransform.SetLocation(FVector(FMath::RandRange(-3.0f,3.0f),1.f,FMath::RandRange(-3.0f,3.0f)));
	APawn* pawnSpawned = GetWorld()->SpawnActorDeferred<APawn>(GetCharacterToSpawn(), startingTransform,
					nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);		
	if (!pawnSpawned)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawn character failed"));
		return nullptr;
	}

	const ATagCharacter* tagCharacter = Cast<ATagCharacter>(pawnSpawned);	
	if (!tagCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn spawned is not a tag character"));
		return nullptr;
	}
	UGameplayStatics::FinishSpawningActor(pawnSpawned, startingTransform);
	return pawnSpawned;
}

TSubclassOf<APawn> UTagSpawnComponent::GetCharacterToSpawn() const
{
	const TSubclassOf<APawn> classToSpawn = dataAsset ? dataAsset->TagCharacterClass() : nullptr;
	return classToSpawn;
}