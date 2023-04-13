// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.h"
#include "Office.generated.h"

UCLASS(BlueprintType)
class MYPROJECT_API AOffice : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOffice();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
