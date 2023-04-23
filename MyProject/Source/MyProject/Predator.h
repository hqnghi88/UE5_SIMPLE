// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Predator.generated.h"

UCLASS(BlueprintType)
class MYPROJECT_API APredator : public ACharacter
{
	GENERATED_BODY()

private:
	// Basic properties
	int32 id=0;
	FVector position;
	FRotator heading;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* StaticMesh; //Graphical representation 
	UAnimationAsset* ANIM_Lion_Run;
public:
	bool dead=false;
	FString fname;
	// Sets default values for this character's properties
	APredator();

	// Sets customized values for this character's properties
	void Init(int32 ID, float x, float y, float z, float heading);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	void End();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// get and set Predator parameters
	int32 GetID();
	FString GetName();
	void SetID(int32 ID);
	int32 GetX();
	int32 GetY();
	int32 GetZ();
	void SetPosition(float x, float y, float z, float heading);
};
