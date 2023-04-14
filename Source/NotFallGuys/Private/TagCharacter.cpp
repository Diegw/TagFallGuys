#include "TagCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TagCharacterDataAsset.h"
#include "TagGameMode.h"
#include "TagPlayerState.h"
#include "Kismet/GameplayStatics.h"

ATagCharacter::ATagCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	TagCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Tag Collider"));
	TagCollider->SetupAttachment(RootComponent);

	bReplicates = true;
}

void ATagCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraBoom->TargetArmLength = characterDataAsset->CameraDistance();
	TagCollider->OnComponentBeginOverlap.AddDynamic(this, &ATagCharacter::OnOverlapBegin);
	TagCollider->OnComponentEndOverlap.AddDynamic(this, &ATagCharacter::OnOverlapEnd);
}

void ATagCharacter::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	if(tagTimer > 0.0f) tagTimer -= deltaSeconds;
}

void ATagCharacter::OnOverlapBegin(UPrimitiveComponent* componentOverlapped, AActor* otherActor,
                                   UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& hitResult)
{
	if(tagTimer > 0) return;
	const APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	if(!playerController || !playerController->IsLocalController()) return;
	if(!otherActor || !GetOwner() || otherActor->GetOwner() == GetOwner()) return;
	if(overlappingActors.Contains(otherActor)) return;
	overlappingActors.Add(otherActor);
	CheckNewTag(otherActor);
}

void ATagCharacter::OnOverlapEnd(UPrimitiveComponent* componentOverlapped, AActor* otherActor,
		UPrimitiveComponent* otherComponent, int otherBodyIndex)
{
	if(otherActor == nullptr || otherActor == GetOwner()) return;
	if(!overlappingActors.Contains(otherActor)) return;
	overlappingActors.Remove(otherActor);
}

void ATagCharacter::CheckNewTag(AActor* otherActor)
{
	ATagPlayerState* myPlayer = GetPlayerState<ATagPlayerState>();
	ATagPlayerState* otherPlayer = Cast<APawn>(otherActor)->GetPlayerState<ATagPlayerState>();
	if(!myPlayer || !otherPlayer) return;
	if(!myPlayer->GetIsTagged()) return;
	if(otherPlayer->GetIsTagged()) return;
	tagTimer = 3.0f;
	UE_LOG(LogTemp, Error, TEXT("New Tag"));
	SERVER_NewTag(myPlayer, otherPlayer);
}

bool ATagCharacter::SERVER_NewTag_Validate(APlayerState* playerTagging, APlayerState* playerTagged) { return true; }
void ATagCharacter::SERVER_NewTag_Implementation(APlayerState* playerTagging, APlayerState* playerTagged)
{
	GetWorld()->GetAuthGameMode<ATagGameMode>()->SetNewTagPlayer(playerTagging, playerTagged);
}

void ATagCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction(characterDataAsset->JumpInputName(), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(characterDataAsset->JumpInputName(), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis(characterDataAsset->MoveXInputName(), this, &ATagCharacter::MoveForward);
	PlayerInputComponent->BindAxis(characterDataAsset->MoveYInputName(), this, &ATagCharacter::MoveSideway);

	PlayerInputComponent->BindAxis(characterDataAsset->RotateXInputName(), this, &ATagCharacter::RotateTurnAt);
	PlayerInputComponent->BindAxis(characterDataAsset->RotateYInputName(), this, &ATagCharacter::RotateLookAt);
}

void ATagCharacter::RotateTurnAt(float axisValue)
{
	if (axisValue == 0.0f) return;
	const float turnAtSpeed = characterDataAsset ? characterDataAsset->TurnAtSpeed() : 1;
	AddControllerYawInput(axisValue * turnAtSpeed * GetWorld()->GetDeltaSeconds());
}

void ATagCharacter::RotateLookAt(float axisValue)
{
	if (axisValue == 0.0f) return;
	const float lookAtSpeed = characterDataAsset ? characterDataAsset->LookAtSpeed() : 1;
	AddControllerPitchInput(axisValue * lookAtSpeed * GetWorld()->GetDeltaSeconds());
}

void ATagCharacter::MoveForward(float axisValue)
{
	if (axisValue == 0.0f) return;
	AddMovementInput(GetWorldCharacterVector(EAxis::X), axisValue);
}

void ATagCharacter::MoveSideway(float axisValue)
{
	if (axisValue == 0.0f) return;
	AddMovementInput(GetWorldCharacterVector(EAxis::Y), axisValue);
}

FVector ATagCharacter::GetWorldCharacterVector(EAxis::Type axisType) const
{
	if(!Controller) return FVector::ZeroVector;
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(axisType);
	return direction;
}

void ATagCharacter::SetInputState(bool enable)
{
	CLIENT_ToggleInput(enable);	
}

bool ATagCharacter::CLIENT_ToggleInput_Validate(bool enable) { return true; }
void ATagCharacter::CLIENT_ToggleInput_Implementation(bool enable)
{
	ToggleInput(enable);
}

void ATagCharacter::ToggleInput(bool enable)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
	if (controller == nullptr)
	{
		return;
	}
	if (enable)
	{
		EnableInput(controller);
	}
	else
	{
		DisableInput(controller);
	}
}
