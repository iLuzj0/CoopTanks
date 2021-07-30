// // Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialFunctionInterface.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

#include "GeneralBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FUNKYTOOLS_API UGeneralBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** Returns true if the function was found & executed correctly. */
	UFUNCTION(BlueprintCallable, Category = "Funky Tools|General")
		static bool CallFunctionByName(UObject* Target, FName FunctionName);

	UFUNCTION(BlueprintCallable, Category = "Funky Tools|General")
		static void SetActorLabel(AActor* InActor, FString NewName);
	
	UFUNCTION(BlueprintPure, Category = "Funky Tools|General")
		static FString ByteArrayToString(TArray<uint8> ArrayIn);
	
	/** Works in editor only */
	UFUNCTION(BlueprintCallable, Category = "Funky Tools|InEditor")
		static void GetMaterialDependentFunctions(UMaterial* Material, TArray<UMaterialFunctionInterface*>& DependentFunctions);
		static bool IterateMaterialDependentFunctions(UMaterial* Material, TFunctionRef<bool(UMaterialFunctionInterface*)> Predicate);

	UFUNCTION(BlueprintCallable, Category = "Funky Tools|Randomization")
		static TArray<FTransform> GetRandomVoxelTransforms(UPARAM(ref) UBoxComponent* SpawnRange, float Seed, float VoxelSize = 100.f, float Frequency = 10.f, float Amplitude = 10.f, float Threshold = 0.f);
	
	UFUNCTION(BlueprintCallable, Category = "Funky Tools|Instancing")
		static void RemoveInstancesOutsideSphere(UPARAM(ref) UHierarchicalInstancedStaticMeshComponent* HISM, FVector Center, float Radius, bool bWorldSpace = false);

	UFUNCTION(BlueprintCallable, Category = "Funky Tools|Instancing")
		static void OffsetAndLoopInstancesInX(UPARAM(ref) UHierarchicalInstancedStaticMeshComponent* HISM, float LoopLengthX, float OffsetX);
	
};
