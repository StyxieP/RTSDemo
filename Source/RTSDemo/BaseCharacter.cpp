// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ABaseCharacter::ABaseCharacter()
{

	//set up centre sphere
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->AttachTo(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Getmaterial(TEXT("Material'/Game/Scenes/GeorgesFolder/WorldTextures/Black.Black'"));
	
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	SphereMesh->SetMaterial(0, Getmaterial.Object);



	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;



	// Create a camera arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	
	CameraArm->SetupAttachment(SphereMesh);
	CameraArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	CameraArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraArm->TargetArmLength = 800.f; //this value conrtols zoom
	
	



	// Create a camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // freeze camera rotation



	// Create crosshair decal
	Crosshair = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	Crosshair->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Scenes/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		Crosshair->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	Crosshair->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	Crosshair->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());



	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Crosshair != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = CameraComponent->GetComponentLocation();
				FVector EndLocation = CameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				Crosshair->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			Crosshair->SetWorldLocation(TraceHitResult.Location);
			Crosshair->SetWorldRotation(CursorR);
		}
	}
}

/* // Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

} */

