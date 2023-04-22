// Fill out your copyright notice in the Description page of Project Settings.

#include "GamaActionsPredator.h"
#include "GamaClient.h"
#include "ExpParameter.h"
#include "Math/Vector.h"
#include "Common/TcpSocketBuilder.h"
#include "ObjectHandler.h"
#include "WebSocketTestGameInstance.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"

// Sets default values
AGamaActionsPredator::AGamaActionsPredator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGamaActionsPredator::BeginPlay()
{
	Super::BeginPlay();

	// SetActorTickInterval(1);
}

void AGamaActionsPredator::EndPlay(const EEndPlayReason::Type EndPlayReason)
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
void AGamaActionsPredator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWebSocketTestGameInstance *GI = Cast<UWebSocketTestGameInstance>(GetGameInstance());

	if (GI && GI->client->message_handler->playing)
	{

		int sid = GI->client->message_handler->GetSocketId();
		int eid = GI->client->message_handler->GetExpId();
		GI->client->expression("predator", sid, eid, "to_geojson(predator,'EPSG:4326',['location'])", true); //);
	}
}

void AGamaActionsPredator::SendChange(int type, int32 ID) const
{
}
