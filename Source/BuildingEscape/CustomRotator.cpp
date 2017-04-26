// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "CustomRotator.h"

#define OUT


// Sets default values for this component's properties
UCustomRotator::UCustomRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UCustomRotator::BeginPlay()
{
	Super::BeginPlay();	
}

void UCustomRotator::OpenDoor()
{
	auto Owner = GetOwner();
	FRotator NewRotator(0.f, -angle, 0.f);
	Owner->SetActorRotation(NewRotator);
}

void UCustomRotator::CloseDoor()
{
	auto Owner = GetOwner();
	FRotator NewRotator(0.f, 0.f, 0.f);
	Owner->SetActorRotation(NewRotator);
}

float UCustomRotator::GetTotalWeight() 
{
	TArray<AActor*> OverlappingActors;

	PressuePlate->GetOverlappingActors(OUT OverlappingActors);
	FString names;

	float totalWeight = 0.0f;
	for (auto &Actor : OverlappingActors) {
		names += Actor->GetName();
		auto component = Actor->FindComponentByClass<UPrimitiveComponent>();
		totalWeight += component->GetMass();		
	}	

	if (totalWeight > 0)
		UE_LOG(LogTemp, Warning, TEXT("Total weight: %f, Items: %s"), totalWeight, *names)

	return totalWeight;
}


// Called every frame
void UCustomRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalWeight() > openedWeight)
		OpenDoor();
	else
		CloseDoor();
}

