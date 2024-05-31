// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshFromStatic::AProcMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// initialize objects
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	
	// setup attachments
	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);
}

// Called when the game starts or when spawned
void AProcMeshFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshFromStatic::PostActorCreated()
{
	Super::PostActorCreated();

	GetMeshData();
}

void AProcMeshFromStatic::PostLoad()
{
	Super::PostLoad();

	GetMeshData();
}

// Called every frame
void AProcMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcMeshFromStatic::GetMeshData()
{
	// local static mesh variable, not a component
	UStaticMesh* mesh = baseMesh->GetStaticMesh();

	if (mesh)
	{
		// generates a procedural mesh
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents);
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

void AProcMeshFromStatic::CreateMesh()
{
	if (baseMesh)
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

