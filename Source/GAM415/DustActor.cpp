// Fill out your copyright notice in the Description page of Project Settings.


#include "DustActor.h"
#include "GAM415Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ADustActor::ADustActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// instantiating objects
	collisionBoxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");

	// hierarchy
	RootComponent = collisionBoxComp;
}

// Called when the game starts or when spawned
void ADustActor::BeginPlay()
{
	Super::BeginPlay();

	// calls function when actor is overlapped
	collisionBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADustActor::OnOverlapBegin);
	
}

// Called every frame
void ADustActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADustActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// assign overlappedActor to player character
	AGAM415Character* overlappedActor = Cast<AGAM415Character>(OtherActor);

	// overlap was done by the player
	if (overlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		// assigns a linear color with the RGB floats, plus 1 for alpha
		FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f);

		if (dustP)
		{
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(dustP, OtherComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
			particleComp->SetNiagaraVariableLinearColor(FString("RandColor"), randColor);
		}
	}

}

