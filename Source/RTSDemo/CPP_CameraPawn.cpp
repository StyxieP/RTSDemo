// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CameraPawn.h"

// Sets default values
ACPP_CameraPawn::ACPP_CameraPawn()
{


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ACPP_CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ACPP_CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

