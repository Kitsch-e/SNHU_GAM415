// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIClass.generated.h"

UCLASS()
class GAM415_API ACubeDMIClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* cubeMesh;

	// base material to create DMI
	UPROPERTY(EditAnywhere)
		UMaterialInterface* baseMat;

	// overides material into DMI
	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
