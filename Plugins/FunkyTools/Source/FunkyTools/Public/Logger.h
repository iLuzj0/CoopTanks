// // Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"

#include "Engine.h"

#include "Logger.generated.h"

UENUM()
enum class E_LogType : uint8 {
	INFO = 0 UMETA(DisplayName = "INFO"),
	WARNING = 1 UMETA(DisplayName = "WARNING"),
	SUCCESS = 2 UMETA(DisplayName = "SUCCESS"),
	ERROR = 3 UMETA(DisplayName = "ERROR")
};

USTRUCT(BlueprintType)
struct F_LogProperty
{
	GENERATED_BODY()

	FColor Color;
	FString Prefix;
	float Duration;
};

UCLASS()
class FUNKYTOOLS_API ULogger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static TMap<E_LogType, F_LogProperty> LogProperties;

	UFUNCTION(BlueprintCallable, meta = (HidePin="Target", DefaultToSelf="Target", Keywords = "logger log debug"), Category = "Funky Tools|Logger")
	static void Log(UObject* Target, E_LogType Type, FString Content, bool OneFrame);
};
