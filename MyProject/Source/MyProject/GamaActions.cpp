// Fill out your copyright notice in the Description page of Project Settings.

#include "GamaActions.h"
#include "GamaClient.h"
#include "ExpParameter.h"
#include "Math/Vector.h" 
#include "Common/TcpSocketBuilder.h"
#include "ObjectHandler.h"
#include "WebSocketTestGameInstance.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"

// Sets default values
AGamaActions::AGamaActions()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGamaActions::BeginPlay()
{
	Super::BeginPlay();
	// SetActorTickInterval(2); 
	// //ObjHandler = new ObjectHandler();

	// // Spawn an instance of ObjectHandlerr in the map in a place far from the objects
	// UWorld* CurrentWorld = GetWorld();
	// const FVector* Loc = new FVector(-1000, -1000, -1000);
	// ObjHandler = (AObjectHandler*)CurrentWorld->SpawnActor(AObjectHandler::StaticClass(), Loc);
}

void AGamaActions::EndPlay(const EEndPlayReason::Type EndPlayReason)
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
void AGamaActions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

	// UWebSocketTestGameInstance* GI = Cast<UWebSocketTestGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI && GI->client->message_handler->IsConnected())
	{
		// read the model
		if (first && GI->client->message_handler->GetSocketId() > 0)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "loading");
			FString current_path = FPaths::ProjectDir();
			FString url = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*(current_path + "../MobilityModel/models/Grid Model.gaml"));
			FString model = "grid_model";
			GI->client->load(GI->client->message_handler->GetSocketId(), url, model);
			first = false;
		}

		// play command
		if (!played && GI->client->message_handler->GetExpId() > 0)
		{
			GI->client->play(GI->client->message_handler->GetSocketId(), GI->client->message_handler->GetExpId(), true);
			played = true;
		}
	} 
}

void AGamaActions::SendChange(int type, int32 ID) const
{
	// FString change_msg = FString("{ \"type\": ") + FString::FromInt(type) + FString(", \"id\": ") + FString::FromInt(ID) + FString("}\n");
	// int32 BytesSent;
	// TcpSocket->Send((const uint8 *)TCHAR_TO_ANSI(*change_msg), change_msg.Len(), BytesSent);
}
