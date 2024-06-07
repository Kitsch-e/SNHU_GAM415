// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrian.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrian::APerlinProcTerrian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	RootComponent = ProcMesh;

	// array storing the tangent data for the vertices
	//TArray<FProcMeshTangent> Tangents;
}

// Called when the game starts or when spawned
void APerlinProcTerrian::BeginPlay()
{
	Super::BeginPlay();

	// array storing the tangent data for the vertices
	TArray<FProcMeshTangent> Tangents;

	CreateVertices();
	CreateTriangles();
	// generates normal and tangent information
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);
	// generates a mesh section
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	ProcMesh->SetMaterial(0, terrainMat);
}

// Called every frame
void APerlinProcTerrian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrian::AlterMesh(FVector impactPoint)
{
	// loop through every vertex
	for (int i = 0; i < Vertices.Num(); i++)
	{
		// find where to generate terrian
		FVector tempVector = impactPoint - this->GetActorLocation();

		// if vertex at location is less than the perlin noise radius
		if (FVector(Vertices[i] - tempVector).Size() < perlinRadius)
		{
			// set depth offset
			Vertices[i] = Vertices[i] - perlinDepth;
			// add vertex to procedural mesh
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrian::CreateVertices()
{
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			// creating Z using X and Y values
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			// debug message printing Z value
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));
			// adding data to vertices and UV
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
			//Normals.Add(VectorNormalize(FVector(X * Scale, Y * Scale, Z)));
		}
	}
}

void APerlinProcTerrian::CreateTriangles()
{
	// local variable used to generate triangle data
	int Vertex = 0;

	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			// adds triangle vertex points based on the Y - value
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			//Normals.Add(VectorNormalize(FVector(Vertex, Vertex + 1, Vertex + YSize + 1)));  // normal data for triangle

			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);
			//Normals.Add(VectorNormalize(FVector(Vertex + 1, Vertex + YSize + 2, Vertex + YSize + 1)));  // normal data for triangle

			Vertex++;
		}
		Vertex++;
	}
}

