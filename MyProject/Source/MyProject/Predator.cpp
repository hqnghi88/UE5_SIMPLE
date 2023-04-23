// Fill out your copyright notice in the Description page of Project Settings.

#include "Predator.h"
#include "WebSocketTestGameInstance.h"
#include <string>

// Sets default values
APredator::APredator()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values for attributes
	id = 0;
	position.X = 0;
	position.Y = 0;
	position.Z = 0;
 

	// 	
	StaticMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	// None
	USkeletalMesh *mesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/AfricanAnimalsPack/LionAndLioness/Meshes/SK_Lion_LOD0.SK_Lion_LOD0'")).Object;

	StaticMesh->SetSkeletalMeshAsset(mesh);
	StaticMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);  
	ANIM_Lion_Run= ConstructorHelpers::FObjectFinder<UAnimationAsset>(TEXT("/Script/Engine.AnimSequence'/Game/AfricanAnimalsPack/LionAndLioness/Animations/ANIM_Lion_Run.ANIM_Lion_Run'")).Object;
	 
	  
	 
	StaticMesh->OverrideAnimationData(ANIM_Lion_Run);
	
	StaticMesh->SetCollisionProfileName(TEXT("OverlapAll")); 
	// StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetMobility(EComponentMobility::Movable);
	RootComponent = StaticMesh;
}

void APredator::Init(int32 ID, float x, float y, float z, float rotation)
{
	// Set values for attributes
	id = ID;
	position.X = x;
	position.Y = y;
	position.Z = z;
	heading = FRotator(0, rotation, 0);
	fname = FString("Predator" + FString(std::to_string(ID).c_str()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "init" + GetName());

	// not needed anymore
	// SetActorLocationAndRotation(position, heading);
}

// Called when the game starts or when spawned
void APredator::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->PlayAnimation(ANIM_Lion_Run,true);
}

// void APredator::EndPlay(const EEndPlayReason::Type EndPlayReason)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "destroy " + FString(std::to_string(id).c_str()));
// 	UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

// 	if (GI && GI->client->message_handler->playing)
// 	{
// 		GI->client->expression(GI->client->message_handler->GetSocketId(), GI->client->message_handler->GetExpId(), "ask Predator(" + FString(std::to_string(id).c_str()) + "){do die;}", true); //);
// 	}
// 	Super::EndPlay(EndPlayReason);
// }

void APredator::End()
{
	if (!dead)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "destroy " + FString(std::to_string(id).c_str()));
		UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

		if (GI && GI->client->message_handler->playing)
		{
			GI->client->expression("diepredator",GI->client->message_handler->GetSocketId(), GI->client->message_handler->GetExpId(), "ask predator(" + FString(std::to_string(id).c_str()) + "){do die;}", true); //);
			dead = true;
		}
	}
}
// Called every frame
void APredator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APredator::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FString APredator::GetName()
{
	// return "Predator";
	// return "Predator" + FString(std::to_string(id).c_str());

	return FString(fname);
}
int32 APredator::GetID()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "init" + FString(std::to_string(id).c_str()));
	return id;
}

void APredator::SetID(int32 ID)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "init" + FString(std::to_string(id).c_str()));
	id = ID;
}

int32 APredator::GetX()
{
	return position.X;
}

int32 APredator::GetY()
{
	return position.Y;
}

int32 APredator::GetZ()
{
	return position.Z;
}

void APredator::SetPosition(float x, float y, float z, float rotation)
{
	position.X = x;
	position.Y = y;
	position.Z = z;
	this->heading = FRotator(0, rotation, 0);
	SetActorLocation(position);
	//SetActorLocationAndRotation(position, heading, true);
}
