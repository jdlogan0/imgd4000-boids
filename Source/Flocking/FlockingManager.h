// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
    GENERATED_BODY()

    void Init( UWorld *world, UStaticMeshComponent *mesh );
    void Flock();

private:
    UWorld *World;
    bool initialized;
    TArray<class AAgent *> Agents;
    FVector rule1(int agentNum);
    FVector rule2(int agentNum);
    FVector rule3(int agentNum);
    FVector limit_velocity(FVector velocity);
    FVector bound_position(int agentNum);
    FVector tend_to_place(int agentNum);
    FVector MAX = FVector(1500.0f, 1500.0f, 1500.0f);
    FVector MIN = FVector(-1500.0f, -1500.0f, -1500.0f);
    FVector target = FVector(0,0,0);
};
