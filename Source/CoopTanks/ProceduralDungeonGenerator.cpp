// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralDungeonGenerator.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProceduralDungeonGenerator::AProceduralDungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProceduralDungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceduralDungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRoomInformation AProceduralDungeonGenerator::RoomMakeFloorArea(FIntVector InRoomLocation) const
{
	const FIntVector RootLocation = InRoomLocation;
	TArray<FIntVector> Tiles;
	TArray<int32> ExtentsX;
	TArray<int32> ExtentsY;
	FRoomInformation RoomInformation;

	const int OutX = UKismetMathLibrary::RandomIntegerInRangeFromStream(
	MinRoomSize, MaxRoomSize,InStream);

	const int OutY = UKismetMathLibrary::RandomIntegerInRangeFromStream(
	MinRoomSize, MaxRoomSize, InStream);

	for (int i = 0; i < (OutX * OutY); i++)
	{
		Tiles.Add(FIntVector(
			(i / OutY) + RootLocation.X,
			(i % OutY) + RootLocation.Y,
			RootLocation.Z
		));
		ExtentsX.Add(Tiles[i].X);
		ExtentsY.Add(Tiles[i].Y);
	}

	RoomInformation.FloorTiles = Tiles;
	RoomInformation.FloorLocation = RootLocation;
	RoomInformation.Extents = FIntVector(ExtentsX.Max(), ExtentsY.Max(), 0);
	return RoomInformation;
}
