// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

// forward declaration to access player character
class GAM415Character;

UCLASS()
class GAM415_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// portal's mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* portalMesh;

	// portal's scene capture component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	// arrow for changing the portal pivot
	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow;

	// portal's render target, which tells the scene capture what to display
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	UPROPERTY(EditAnywhere)
	UBoxComponent* collisionComp;

	// allows us to select which portal to connect to
	UPROPERTY(EditAnywhere)
	APortal* otherPortal;

	// material used by the portal
	UPROPERTY(EditAnywhere)
	UMaterialInterface* portalMat;

	UFUNCTION()
	// activates portal when player overlaps it
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// called within OnOverlapBegin to set isTeleporting within the character to false
	// must be here so that we can use a timer function and wait before switching the bool back
	UFUNCTION()
	void SetBool(AGAM415Character* playerChar);

	// called to update the portal
	UFUNCTION()
	void UpdatePortals();
};
