// Fill out your copyright notice in the Description page of Project Settings.

#include "GamaActionsBBox.h"
#include "GamaClient.h"
#include "ExpParameter.h"
#include "Math/Vector.h" 
#include "Common/TcpSocketBuilder.h"
#include "ObjectHandler.h"
#include "WebSocketTestGameInstance.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"

// Sets default values
AGamaActionsBBox::AGamaActionsBBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGamaActionsBBox::BeginPlay()
{
	Super::BeginPlay(); 

	// SetActorTickInterval(2); 
	// // Spawn an instance of ObjectHandlerr in the map in a place far from the objects
	// UWorld* CurrentWorld = GetWorld();
	// const FVector* Loc = new FVector(-1000, -1000, -1000);
	// ObjHandler = (AObjectHandler*)CurrentWorld->SpawnActor(AObjectHandler::StaticClass(), Loc);
}

void AGamaActionsBBox::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	// GetWorld()->DestroyActor(ObjHandler);
	// ISocketSubsystem *SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	// if (SocketSubsystem != nullptr)
	// {
	// 	SocketSubsystem->DestroySocket(TcpSocket);
	// }
	// client->stop(message_handler->GetSocketId(), message_handler->GetExpId());
	// delete message_handler;
	// delete client;
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AGamaActionsBBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

	if (GI && GI->client->message_handler->playing)
	{

		// read the model
		// if (first && GI->message_handler->GetSocketId() > 0)
		// {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "retrieve");
		// 	FString current_path = FPaths::ProjectDir();
		// 	FString url = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*(current_path + "../MobilityModel/models/Grid Model.gaml"));
		// 	FString model = "grid_model";
		// 	GI->client->load(GI->message_handler->GetSocketId(), url, model);
		// 	first = false;
		// }

		// // play command
		// if (!played && GI->message_handler->GetExpId() > 0)
		// {
		// 	GI->client->play(GI->message_handler->GetSocketId(), GI->message_handler->GetExpId(), true);
		// 	played = true;
		// }
	} 
}

void AGamaActionsBBox::SendChange(int type, int32 ID) const
{
	
}
