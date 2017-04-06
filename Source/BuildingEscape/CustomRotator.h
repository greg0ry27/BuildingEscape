// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CustomRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UCustomRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

public:	

	UPROPERTY(VisibleAnywhere)
	float angle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressuePlate;

	UPROPERTY(VisibleAnywhere)
	AActor* Pawn;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};