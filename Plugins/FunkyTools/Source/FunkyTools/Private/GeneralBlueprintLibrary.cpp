// // Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.


#include "GeneralBlueprintLibrary.h"

bool UGeneralBlueprintLibrary::CallFunctionByName(UObject* Target, FName FunctionName)
{
	if (Target)
	{
		if (UFunction* Function = Target->FindFunction(FunctionName))
		{
			Target->ProcessEvent(Function, nullptr);
			return true;
		}
		return false;
	}
	return false;
}

void UGeneralBlueprintLibrary::SetActorLabel(AActor* InActor, FString NewName)
{
	InActor->SetActorLabel(NewName);
}

FString UGeneralBlueprintLibrary::ByteArrayToString(TArray<uint8> ArrayIn)
{
	int32 Count = ArrayIn.Num();
	int32 In = 0;
	
	FString Result;
	Result.Empty(Count);

	while (Count)
	{
		Result += TCHAR(ArrayIn[In]);

		++In;
		Count--;
	}
	return Result;
}

void UGeneralBlueprintLibrary::GetMaterialDependentFunctions(UMaterial* Material,
                                                             TArray<UMaterialFunctionInterface*>& DependentFunctions)
{
	IterateMaterialDependentFunctions(Material, [&DependentFunctions](UMaterialFunctionInterface* MaterialFunction) -> bool
	{
		DependentFunctions.AddUnique(MaterialFunction);
		return true;
	});
}

bool UGeneralBlueprintLibrary::IterateMaterialDependentFunctions(UMaterial* Material,
	TFunctionRef<bool(UMaterialFunctionInterface*)> Predicate)
{
	for (UMaterialExpression* Expression : Material->Expressions)
	{
		if (UMaterialExpressionMaterialFunctionCall* FunctionCall = Cast<UMaterialExpressionMaterialFunctionCall>(Expression))
		{
			if (!FunctionCall->IterateDependentFunctions(Predicate))
			{
				return false;
			}
		}
	}
	
	return true;
}

TArray<FTransform> UGeneralBlueprintLibrary::GetRandomVoxelTransforms(UBoxComponent* SpawnRange, float Seed, float VoxelSize,
	float Frequency, float Amplitude, float Threshold)
{
	TArray<FTransform> Result;

	const int HalfX = static_cast<int>(SpawnRange->GetScaledBoxExtent().X / VoxelSize);
	const int HalfY = static_cast<int>(SpawnRange->GetScaledBoxExtent().Y / VoxelSize);
	const int HalfZ = static_cast<int>(SpawnRange->GetScaledBoxExtent().Z / VoxelSize);
	
	for (int x = -HalfX; x < HalfX; x++)
	{
		for (int y = -HalfY; y < HalfY; y++)
		{
			const FVector2D CurrentLocation = FVector2D((x + Seed) / Frequency, (y  + Seed) / Frequency);
			const float NoiseValue_2D = FMath::PerlinNoise2D(CurrentLocation) * Amplitude;
			const int Z_Axis = FMath::FloorToInt(NoiseValue_2D);
    
			for (int z = -Z_Axis + HalfZ - 1; z > -Z_Axis - HalfZ; z--)
			{
				FVector PerlinNoise3D_Location = FVector((x + Seed) / Frequency, (y + Seed) / Frequency, (z + Seed) / Frequency);
				const float NoiseValue_3D = FMath::PerlinNoise3D(PerlinNoise3D_Location);
				const bool bCanSpawnVoxel = NoiseValue_3D <= Threshold;
    			
				if (bCanSpawnVoxel)
				{
					Result.Add(FTransform(
						FVector(
							static_cast<float>(x) * VoxelSize + SpawnRange->GetComponentLocation().X,
							static_cast<float>(y) * VoxelSize + SpawnRange->GetComponentLocation().Y,
							static_cast<float>(z) * VoxelSize + SpawnRange->GetComponentLocation().Z
						)
					));
				}
			}
		}
	}

	return Result;
}

void UGeneralBlueprintLibrary::RemoveInstancesOutsideSphere(UHierarchicalInstancedStaticMeshComponent* HISM,
	FVector Center, float Radius, bool bWorldSpace)
{
	TArray<int32> All = HISM->GetInstancesOverlappingSphere(Center, 1000000000, true);
	const TArray<int32> Inside = HISM->GetInstancesOverlappingSphere(Center, Radius, bWorldSpace);
	TArray<int32> ToRemove;

	for (int i = All.Num() - 1; i > 0; i--)
	{
		if (!Inside.Contains(All[i])) ToRemove.Add(All[i]);
	}

	HISM->RemoveInstances(ToRemove);
}

void UGeneralBlueprintLibrary::OffsetAndLoopInstancesInX(UHierarchicalInstancedStaticMeshComponent* HISM,
	float LoopLengthX, float OffsetX)
{
	FTransform Transform;
	FVector NewLocation;
	
	for (int i = 0; i < HISM->GetInstanceCount(); i++)
	{
		HISM->GetInstanceTransform(i, Transform, false);

		NewLocation.X = FGenericPlatformMath::Fmod(LoopLengthX + Transform.GetLocation().X + OffsetX, LoopLengthX * 2) - LoopLengthX;
		NewLocation.Y = Transform.GetLocation().Y;
		NewLocation.Z = Transform.GetLocation().Z;
		Transform.SetLocation(NewLocation);

		HISM->UpdateInstanceTransform(i, Transform, false, false, true);
	}

	// Update child actors
	TArray<AActor*> ChildActors;
	HISM->GetOwner()->GetAttachedActors(ChildActors);
	
	for(AActor* Child : ChildActors)
	{
		Child->AddActorWorldOffset(HISM->GetOwner()->GetActorForwardVector() * OffsetX);
	}
}