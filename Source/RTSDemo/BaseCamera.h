// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCamera.generated.h"

UCLASS()
class RTSDEMO_API ABaseCamera : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABaseCamera();

    void VerticalMovementCallback(float value);
    void HorizontalMovementCallback(float value);
    void CameraZoomCallback(float value);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraArm; }
    FORCEINLINE class UDecalComponent* GetCursorToWorld() { return Crosshair; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* CameraArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UDecalComponent* Crosshair;

    UPROPERTY(EditAnywhere, Category = Camera)  //sphere to check the centering of the camera
        UStaticMeshComponent* SphereMesh;

};