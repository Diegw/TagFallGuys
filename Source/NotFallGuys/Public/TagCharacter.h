
#pragma once

#include "CoreMinimal.h"
#include "ToggleInputInterface.h"
#include "GameFramework/Character.h"
#include "TagCharacter.generated.h"

class UTagCharacterDataAsset;

UCLASS()
class ATagCharacter : public ACharacter, public IToggleInputInterface
{
	GENERATED_BODY()

public:
	ATagCharacter();
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UFUNCTION(BlueprintImplementableEvent) void SetNewMaterial(bool isTagged);
	void CheckNewTag(AActor* otherActor);
	UFUNCTION(Server, WithValidation, Reliable) void SERVER_NewTag(APlayerState* playerTagging, APlayerState* playerTagged);
		
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetInputState(bool enable) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* TagCollider;
	
	UPROPERTY(EditDefaultsOnly) UTagCharacterDataAsset* characterDataAsset;
	TSet<AActor*> overlappingActors;
	float tagTimer;
	
	void MoveForward(float axisValue);
	void MoveSideway(float axisValue);
	FVector GetWorldCharacterVector(EAxis::Type axisType) const;
	
	void RotateTurnAt(float axisValue);
	void RotateLookAt(float axisValue);

	UFUNCTION(Client, WithValidation, Reliable) void CLIENT_ToggleInput(bool enable);
	void ToggleInput(bool enable);
	
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* componentOverlapped, AActor* otherActor,
		UPrimitiveComponent* otherComponent, int otherBodyIndex, bool fromSweep, const FHitResult& hitResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* componentOverlapped, AActor* otherActor,
		UPrimitiveComponent* otherComponent, int otherBodyIndex);
};
