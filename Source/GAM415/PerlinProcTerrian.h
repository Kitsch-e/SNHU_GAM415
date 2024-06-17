// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "KismetProceduralMeshLibrary.h"  // needed to instantiate Tangents
#include "PerlinProcTerrian.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM415_API APerlinProcTerrian : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrian();

	// x-width of our procedural terrain
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	// y-height of our procedural terrain
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	// height of the perlin noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	// controls the scale of the noise for the perlin noise
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	// controls the scale of the procederal terrain
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	// scale of the UVs applied to the procedural terrain
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0;

	// radius of hole
	UPROPERTY(EditAnywhere)
	float perlinRadius;

	// height of the hole
	UPROPERTY(EditAnywhere)
	FVector perlinDepth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// material used by the terrian
	UPROPERTY(EditAnywhere)
	UMaterialInterface* terrainMat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// function that is called when we want mesh to be altered
	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	// mesh object storing the procedural terrain
	UProceduralMeshComponent* ProcMesh;

	// array storing x, y, z positions of triangle vertices
	TArray<FVector> Vertices;
	// array storing triangles made with Vertices array
	TArray<int> Triangles;
	// array storing the UV data of the triangles
	// UVs stored in values between 0 - 1
	TArray<FVector2D> UV0;
	// array storing the normal data of the triangles
	TArray<FVector> Normals;
	// array storing the up vertex colors
	TArray<FColor> UpVertexColors;

	// unused, here to section the terrain; currently a single objects
	int sectionID = 0;

	// creates the vertices, called before CreateTriangles()
	void CreateVertices();
	// creates the triangles, uses data created from CreateVertices()
	void CreateTriangles();
};
