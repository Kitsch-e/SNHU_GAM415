// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcPlane.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProcPlane::AProcPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
}

// Called when the game starts or when spawned
void AProcPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcPlane::PostActorCreated()
{
	Super::PostActorCreated();

	CreateMesh();
	if (planeMat)
	{
		procMesh->SetMaterial(0, planeMat);
	}
}

void AProcPlane::PostLoad()
{
	Super::PostLoad();

	CreateMesh();
	if (planeMat)
	{
		procMesh->SetMaterial(0, planeMat);
	}
}

// Called every frame
void AProcPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcPlane::CreateMesh()
{
	procMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}



