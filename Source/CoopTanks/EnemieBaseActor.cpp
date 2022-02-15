// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemieBaseActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AEnemieBaseActor::AEnemieBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemieBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemieBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
FRotator AEnemieBaseActor::FindActorToShootAt(FVector PlayerToShootAt, float DeltaTime, float TowerTurningSpeed)
{
	//Znalezienie na co patrzy aktor
	FRotator FoundPlayerLookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		this->GetActorLocation(), PlayerToShootAt
	);

	//Konwertowanie FoundPlayerLookAtRotation aby był kompatybilny z funkcja RInterpTo
	FRotator ConvertedFoundPlayerLookAtRotation = FRotator(
		0.0, FoundPlayerLookAtRotation.Yaw, 0.0
	);

	//Zwracanie rotacji na jaka ma patrzec aktor
	return FMath::RInterpTo(
		this->GetActorRotation(), ConvertedFoundPlayerLookAtRotation, DeltaTime, TowerTurningSpeed
	);
}

