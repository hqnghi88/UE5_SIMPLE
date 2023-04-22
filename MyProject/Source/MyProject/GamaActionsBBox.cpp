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

	// SetActorTickInterval(1);
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

		int sid = GI->client->message_handler->GetSocketId();
		int eid = GI->client->message_handler->GetExpId();
		GI->client->expression("BBox", sid, eid, "to_geojson(BBox,'EPSG:4326',['location'])", true); //);
	}
}

void AGamaActionsBBox::SendChange(int type, int32 ID) const
{
}
