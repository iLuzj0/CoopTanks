// Fill out your copyright notice in the Description page of Project Settings.


#include "mainRobotPart.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AmainRobotPart::AmainRobotPart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AmainRobotPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AmainRobotPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AmainRobotPart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AmainRobotPart::BodyRotateControll(UStaticMeshComponent* inBodyComponent, FRotator inGunTarget)
{
	FRotator BodyRotation = inBodyComponent->GetRelativeRotation();

	float DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(
	FRotator(0.0, BodyRotation.Yaw, 0.0), 
	FRotator(0.0, inGunTarget.Yaw, 0.0)).Yaw;
	float DeltaBodyRotation = (UKismetMathLibrary::NormalizedDeltaRotator(
		PreviewBodyRotation, BodyRotation).Yaw);
	DeltaRotation = UKismetMathLibrary::SignOfFloat(DeltaRotation) * BodyRotationSpeed;

	float RotationForce = (ForceNominal * DeltaRotation) + (DeltaBodyRotation / DeltaSec) * RotationDumping;
	inBodyComponent->AddTorqueInDegrees(FVector(0,0,RotationForce));

	return DeltaRotation;
}
