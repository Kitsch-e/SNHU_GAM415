// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "GAM415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creating objects
	portalMesh = CreateDefaultSubobject<UStaticMeshComponent>("Portal Mesh");
	collisionComp = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture Component");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	// setting up attachments
	RootComponent = collisionComp;
	portalMesh->SetupAttachment(collisionComp);
	sceneCapture->SetupAttachment(portalMesh);
	rootArrow->SetupAttachment(RootComponent);

	// portal mesh ignores all collisions
	portalMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// call the on overlap function
	collisionComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	// hide the portal from its scene capture
	portalMesh->SetHiddenInSceneCapture(true);

	// assign material to portal
	if (portalMat)
	{
		portalMesh->SetMaterial(0, portalMat);
	}
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePortals();
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGAM415Character* playerChar = Cast<AGAM415Character>(OtherActor);

	// cast successful
	if (playerChar)
	{
		// portal goes somewhere
		if (otherPortal)
		{
			// player isn't currently teleporting
			if (!playerChar->isTeleporting)
			{
				// change bool to reflect player action
				playerChar->isTeleporting = true;
				// get the location of the connected portal via its root arrow (pivot)
				FVector teleportLocation = otherPortal->rootArrow->GetComponentLocation();
				// move the player to that portal's location
				playerChar->SetActorLocation(teleportLocation);

				// pause the function before switching bool back to false
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				// binds the timer to our SetBool function
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				// 3rd argument decides how long to wait, final bool is if it should loop
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}

void APortal::SetBool(AGAM415Character* playerChar)
{
	// turn of isTeleporting bool
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

void APortal::UpdatePortals()
{
	// vector storing the distance between the two connected portals.
	FVector portalDistance = this->GetActorLocation() - otherPortal->GetActorLocation();
	// vector storing the location of the player's camera
	// GetPlayerCameraManager ( -, 0), 0 refers to the player
	FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	// vector storing the rotation of the player's camera
	FRotator cameraRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector combinedLocation = cameraLocation + portalDistance;

	// sets the display for the portal based on the location and rotation of the character in reference to the portal's location
	sceneCapture->SetWorldLocationAndRotation(combinedLocation, cameraRotation);
}
