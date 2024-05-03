// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockingManager.h"
#include "Agent.h"
#include "Math/Vector.h"

#define AGENT_COUNT 10

void UFlockingManager::Init( UWorld *world, UStaticMeshComponent *mesh ) {
  UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

  World = world;

  float incr = (PI * 2.f) / AGENT_COUNT;
  for( int i = 0; i < AGENT_COUNT; i++ ) {
    if( World != nullptr ) {
        FRotator rotation = FRotator();

        FVector location = FVector();
        location.X = FMath::FRandRange(MIN.X, MAX.X);
        location.Y = FMath::FRandRange(MIN.Y, MAX.Y);
        location.Z = FMath::FRandRange(MIN.Z, MAX.Z);

        AAgent * agent = World->SpawnActor<AAgent>( location, rotation );
        agent->Init( mesh, i );
        Agents.Add( agent );
    }
  }
    target.X = FMath::FRandRange(MIN.X, MAX.X);
    target.Y = FMath::FRandRange(MIN.Y, MAX.Y);
    target.Z = FMath::FRandRange(MIN.Z, MAX.Z);

  initialized = true;
}

FVector UFlockingManager::rule1(int agentNum) {
    AAgent* agent = Agents[agentNum];
    FVector agentVec = FVector(0,0,0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != agentNum) {
            agentVec += Agents[i]->GetActorLocation();
        }
    }
    agentVec = agentVec/(AGENT_COUNT-1);
    agentVec = (agentVec - agent->GetActorLocation())/700;
    return agentVec;
    
}
FVector UFlockingManager::rule2(int agentNum) {
    AAgent* agent = Agents[agentNum];
    FVector agentVec = FVector(0,0,0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != agentNum) {
            float distance = FVector::Dist(Agents[i]->GetActorLocation(), agent->GetActorLocation());
            if (distance < 150) {
                agentVec -= (Agents[i]->GetActorLocation() - agent->GetActorLocation());
            }
        }
    }
    return agentVec;
}
FVector UFlockingManager::rule3(int agentNum) {
    AAgent* agent = Agents[agentNum];
    FVector agentVec = FVector(0,0,0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != agentNum) {
            agentVec += Agents[i]->Velocity;
        }
    }
    agentVec = agentVec/(AGENT_COUNT-1);
    agentVec = (agentVec - agent->Velocity)/6;
    return agentVec;
}

FVector UFlockingManager::bound_position(int agentNum) {
    AAgent* agent = Agents[agentNum];
    FVector agentVec = agent->GetActorLocation();
    FVector offset = FVector(0,0,0);
    
    if (agentVec.X < MIN.X) {
        offset.X = 10;
    }
    else if (agentVec.X > MAX.X) {
        offset.X = -10;
    }
    if (agentVec.Y < MIN.Y) {
        offset.Y = 10;
    }
    else if (agentVec.Y > MAX.Y) {
        offset.Y = -10;
    }
    if (agentVec.Z < MIN.Z) {
        offset.Z = 10;
    }
    else if (agentVec.Z > MAX.Z) {
        offset.Z = -10;
    }
    
    return offset;
}

FVector UFlockingManager::tend_to_place(int agentNum) {
    if ((target - Agents[agentNum]->GetActorLocation()).Size() < 600){
        target.X = FMath::FRandRange(MIN.X, MAX.X);
        target.Y = FMath::FRandRange(MIN.Y, MAX.Y);
        target.Z = FMath::FRandRange(MIN.Z, MAX.Z);
        
        UE_LOG(LogTemp, Warning, TEXT("new target"));
    }
    return (target - Agents[agentNum]->GetActorLocation()) / 10000;
}

FVector UFlockingManager::limit_velocity(FVector velocity) {
    float limit = 15.0;
    FVector newV = velocity;
    if (newV.Size() > limit) {
        newV = newV.GetClampedToMaxSize(limit);
    }
    return newV;
}

void UFlockingManager::Flock() {
    for (int i = 0; i < AGENT_COUNT; i++) {
        FVector v1 = rule1(i);
        FVector v2 = rule2(i);
        FVector v3 = rule3(i);
        FVector v4 = bound_position(i);
        FVector v5 = tend_to_place(i);
        
        FVector v = Agents[i]->Velocity + v1 + v2 + v3 + v4 + v5;
        v = limit_velocity(v);
        Agents[i]->Velocity = v;
    }
    
}
