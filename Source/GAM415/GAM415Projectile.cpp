// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

AGAM415Projectile::AGAM415Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGAM415Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;


	// Create the static mesh representing the projectile
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");

	// Set collision as root component
	RootComponent = CollisionComp;

	// attach static mesh to collision
	ballMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGAM415Projectile::BeginPlay()
{
	Super::BeginPlay();

	/*
	// floats to select a random color
	float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	*/

	// 4Vector with radom values for HSV and full alpha
	//randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);
	//projColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f);

	projColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	// sets up the dynamic material to use the projMat
	projDMIMat = UMaterialInstanceDynamic::Create(projMat, this);

	projDMIMat->SetVectorParameterValue("ProjColor", projColor);

	ballMesh->SetMaterial(0, projDMIMat);
}

void AGAM415Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	if (OtherActor != nullptr)
	{
		/* no longer needed, called from BeginPlay()
		// floats to select a random color
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.f);
		*/

		// float that selects which decal to use
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f);

		// (world, material, size of decal, location, rotation, lifespan (0 = forever)
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), SplatterMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 3.f);
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		// uses the same random color that the projectile uses
		MatInstance->SetVectorParameterValue("Color", projColor);
		MatInstance->SetScalarParameterValue("Frame", frameNum);
	}
}