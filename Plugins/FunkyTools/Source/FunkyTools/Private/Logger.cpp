// // Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.


#include "Logger.h"

// LogType, Color, Prefix, Duration
TMap<E_LogType, F_LogProperty> ULogger::LogProperties = {
		{E_LogType::ERROR, { FColor(255, 0, 0, 255), FString("ERROR: "), 5.0f }},
		{E_LogType::WARNING, { FColor(170, 125, 0, 255), FString("WARNING: "), 5.0f }},
		{E_LogType::SUCCESS, { FColor(0, 255, 0, 255), FString("SUCCESS: "), 5.0f }},
		{E_LogType::INFO, { FColor(0, 255, 255, 255), FString("INFO: "), 5.0f }}
};

void ULogger::Log(UObject* Target, E_LogType Type, FString Content, bool OneFrame)
{
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Log target is nullptr"));

		return;
	}

	FString Prefix = LogProperties.Find(Type)->Prefix + " (" + Target->GetName() + "): ";
	float Duration = (OneFrame == true) ? 0 : LogProperties.Find(Type)->Duration;
	FColor Color = LogProperties.Find(Type)->Color;
	FString OutputString = Prefix + Content;

	GEngine->AddOnScreenDebugMessage(-1, Duration, Color, OutputString);
	if (Type == E_LogType::ERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *OutputString);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);
	}
}