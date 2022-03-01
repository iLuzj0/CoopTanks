// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralDungeonGenerator.generated.h"

struct FRoomInformation
{
	TArray<FIntVector> FloorTiles;
	FIntVector FloorLocation;
	FIntVector Extents;
};

UCLASS()
class COOPTANKS_API AProceduralDungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralDungeonGenerator();
	int32 MaxRoomSize;
	int32 MinRoomSize;
	FRandomStream InStream;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FRoomInformation RoomMakeFloorArea(FIntVector InRoomLocation) const;
};
