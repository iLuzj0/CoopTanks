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
	//Finding actor to look at
	FRotator FoundPlayerLookAtRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerToShootAt);

	//Converting look at rotation to use in reinterpto 
	FRotator ConvertedFoundPlayerLookAtRotation = FRotator(0.0, FoundPlayerLookAtRotation.Yaw, 0.0);

	//Returning location to look at reinterprated by elapsed time
	return FMath::RInterpTo(this->GetActorRotation(), ConvertedFoundPlayerLookAtRotation, DeltaTime, TowerTurningSpeed);
}

