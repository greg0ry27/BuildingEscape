// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "CustomRotator.h"


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
	Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UCustomRotator::OpenDoor()
{
	auto Owner = GetOwner();
	FRotator NewRotator(0.f, -60.f, 0.f);
	Owner->SetActorRotation(NewRotator);
}


// Called every frame
void UCustomRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressuePlate->IsOverlappingActor(Pawn))
		OpenDoor();
	// ...
}

