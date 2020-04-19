// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "GameFramework/Actor.h"
#include "MainCamera.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AOfficeZMainCamera : public AActor
{
	GENERATED_BODY()

public:
	AOfficeZMainCamera();

	UFUNCTION(BlueprintCallable)
	void SetTargetActor(const AActor* actor);

private:
	/** The camera component for this camera */
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	float _pixelsPerUnit = 1.f;

private:
	TWeakObjectPtr<AActor> _targetActor;

private:
	void UpdateCameraLocation(float DeltaTime);
	void SnapCameraLocation(float DeltaTime);

// AActor
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;	


};
/*----------------------------------------------------------------------------------------------------*/