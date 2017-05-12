// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	handleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!handleComponent)
		UE_LOG(LogTemp, Error, TEXT("UPhysicsHandleComponent is not assign to %s"), *this->GetName())

	if (!inputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UInputComponent is not assign to %s"), *this->GetName())
	}
	else 
	{
		inputComponent->BindAction(UGrabber::GRAB, EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction(UGrabber::GRAB, EInputEvent::IE_Released, this, &UGrabber::Release);
	}	
}



void UGrabber::Grab() 
{	
	if (!handleComponent)
		return;

	FVector eyeLocation;
	FRotator eyeRotation;

	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(
		OUT eyeLocation,
		OUT eyeRotation
	);

	FVector lineEnd = eyeLocation + eyeRotation.Vector()*Length;	

	FHitResult					hitResult;
	FCollisionQueryParams		queryParams("Trace", false, GetOwner());
	FCollisionObjectQueryParams objectParam(ECollisionChannel::ECC_PhysicsBody);

	GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		eyeLocation,
		lineEnd,
		objectParam,
		queryParams
	);

	auto hitActor = hitResult.GetActor();
	auto hitComponent = hitResult.GetComponent();	 

	if (hitActor)		
		handleComponent->GrabComponent(
			hitComponent, 
			NAME_None, 
			hitComponent->GetOwner()->GetActorLocation(), 
			true
		);	

}

void UGrabber::Release()
{	
	handleComponent->ReleaseComponent();
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	if (handleComponent->GrabbedComponent) {
		
		FVector eyeLocation;
		FRotator eyeRotation;

		GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(
			OUT eyeLocation,
			OUT eyeRotation
		);

		FVector lineEnd = eyeLocation + eyeRotation.Vector()*Length;

		handleComponent->SetTargetLocation(lineEnd);
	}
}

