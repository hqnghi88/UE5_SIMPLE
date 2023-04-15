// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamaClient.h" 
#include "ObjectHandler.h"
#include "GamaActionsBBox.generated.h"

UCLASS(BlueprintType)
class MYPROJECT_API AGamaActionsBBox : public AActor
{
	GENERATED_BODY()
	
	// Connection constants
	const FString GAMA_URL		= "localhost";
	const FString GAMA_IP		= "127.0.0.1";
	const int GAMA_SERVER_PORT	= 6868;
	const uint16 TCP_PORT		= 8000;
 
	
	// Game logic
	bool first = true;
	bool last = true;
	bool played = false;
	bool tcp_connected = false;
public:	
	// Sets default values for this actor's properties
	AGamaActionsBBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)

	// Send changes to Gama
	void SendChange(int type,int32 ID) const;
	
};
