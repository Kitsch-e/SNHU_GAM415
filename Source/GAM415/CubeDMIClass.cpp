// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIClass.h"
#include "GAM415Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDMIClass::ACubeDMIClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// instantiating objects
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	// hierarchy
	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIClass::BeginPlay()
{
	Super::BeginPlay();

	// calls function when actor is overlapped
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIClass::OnOverlapBegin);


	// checks if baseMat and cubeMesh are instantiated
	if (baseMat)
	{
		// creates a DMI in dmiMat from the normal material, "this" refers to this actor
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	if (cubeMesh)
	{
		// sets the material of the cube to be the DMI
		cubeMesh->SetMaterial(0, dmiMat);
	}
	
}

// Called every frame
void ACubeDMIClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// assign overlappedActor to player character
	AGAM415Character* overlappedActor = Cast<AGAM415Character>(OtherActor);

	// overlap was done by the player
	if (overlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		// assigns a 4vector with the RGB floats, plus 1 for alpha
		FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.f);

		// if dmi is instantiated
		if (dmiMat)
		{
			// sets the parameter "Color" to the 4Vector
			dmiMat->SetVectorParameterValue("Color", randColor);
			// sets the parameter "Darkness" to the X float
			dmiMat->SetScalarParameterValue("Darkness", ranNumX);

			// Note: these names correspond to the parameter names within the material
		}
	}
}


