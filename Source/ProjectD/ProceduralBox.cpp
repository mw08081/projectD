// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralBox.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProceduralBox::AProceduralBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the procedural mesh component
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	RootComponent = ProceduralMesh;

	// Enable physics simulation
	ProceduralMesh->SetSimulatePhysics(true);

	//Get Mesh Section
	Constructor_GetMeshSection();
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, TArray<FColor>(), Tangents, false);
	ProceduralMesh->SetMaterial(0, Material);
	ProceduralMesh->AddCollisionConvexMesh(Vertices);
}

void AProceduralBox::Constructor_GetMeshSection()
{
	if (StaticMesh) {
		//Get Mesh Section
		TArray<FVector> _Vertices;
		TArray<int32> _Triangles;
		TArray<FVector> _Normals;
		TArray<FVector2D> _UVs;
		TArray<FProcMeshTangent> _Tangents;

		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
			StaticMesh,
			LODIndex,
			SectionIndex,
			_Vertices,
			_Triangles,
			_Normals,
			_UVs,
			_Tangents
		);

		Vertices = _Vertices;
		Triangles = _Triangles;
		Normals = _Normals;
		UVs = _UVs;
		Tangents = _Tangents;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("StaticMesh is not set!"));
	}
}

// Called when the game starts or when spawned
void AProceduralBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceduralBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

