// Fill out your copyright notice in the Description page of Project Settings.

#include "People.h"
#include "WebSocketTestGameInstance.h"
#include <string>

// Sets default values
APeople::APeople()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values for attributes
	id = 0;
	position.X = 0;
	position.Y = 0;
	position.Z = 0;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	// Load the car
	UStaticMesh *mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'")).Object;

	StaticMesh->SetStaticMesh(mesh);
	StaticMesh->SetCollisionProfileName(TEXT("OverlapAll"));

	// StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMobility(EComponentMobility::Movable);
	RootComponent = StaticMesh;
}

void APeople::Init(int32 ID, float x, float y, float z, float rotation)
{
	// Set values for attributes
	id = ID;
	position.X = x;
	position.Y = y;
	position.Z = z;
	heading = FRotator(0, rotation, 0);
	fname = FString("People" + FString(std::to_string(ID).c_str()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "init" + GetName());

	// not needed anymore
	// SetActorLocationAndRotation(position, heading);
}

// Called when the game starts or when spawned
void APeople::BeginPlay()
{
	Super::BeginPlay();
}

// void APeople::EndPlay(const EEndPlayReason::Type EndPlayReason)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "destroy " + FString(std::to_string(id).c_str()));
// 	UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

// 	if (GI && GI->client->message_handler->playing)
// 	{
// 		GI->client->expression(GI->client->message_handler->GetSocketId(), GI->client->message_handler->GetExpId(), "ask people(" + FString(std::to_string(id).c_str()) + "){do die;}", true); //);
// 	}
// 	Super::EndPlay(EndPlayReason);
// }

void APeople::End()
{
	if (!dead)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "destroy " + FString(std::to_string(id).c_str()));
		UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

		if (GI && GI->client->message_handler->playing)
		{
			GI->client->expression(GI->client->message_handler->GetSocketId(), GI->client->message_handler->GetExpId(), "ask BBox(" + FString(std::to_string(id).c_str()) + "){do die;}", true); //);
			dead = true;
		}
	}
}
// Called every frame
void APeople::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APeople::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FString APeople::GetName()
{
	// return "People";
	// return "People" + FString(std::to_string(id).c_str());

	return FString(fname);
}
int32 APeople::GetID()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "init" + FString(std::to_string(id).c_str()));
	return id;
}

void APeople::SetID(int32 ID)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "init" + FString(std::to_string(id).c_str()));
	id = ID;
}

int32 APeople::GetX()
{
	return position.X;
}

int32 APeople::GetY()
{
	return position.Y;
}

int32 APeople::GetZ()
{
	return position.Z;
}

void APeople::SetPosition(float x, float y, float z, float rotation)
{
	position.X = x;
	position.Y = y;
	position.Z = z;
	this->heading = FRotator(0, rotation, 0);
	SetActorLocationAndRotation(position, heading, true);
}
