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
	SetActorTickInterval(5); 
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
	if (GI && GI->client->IsConnected())
	{

		// read the model
		if (first && GI->client->GetSocketId() > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "loading");
			FString current_path = FPaths::ProjectDir();
			FString url = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*(current_path + "../MobilityModel/models/Grid Model.gaml"));
			FString model = "grid_model";
			GI->client->load(GI->client->GetSocketId(), url, model);
			first = false;
		}

		// play command
		if (!played && GI->client->GetExpId() > 0)
		{
			GI->client->play(GI->client->GetSocketId(), GI->client->GetExpId(), true);
			played = true;
		}
	}
	// if (played && message_handler->GetExpId() > 0)
	// {
	// // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "expression");
	// 	client->expression(message_handler->GetSocketId(), message_handler->GetExpId(), "to_geojson(BBox,'EPSG:4326',['color'])", "gogo");//);
	// }

	// // Connects to TCP server
	// if (!tcp_connected && message_handler -> IsPlaying())
	// {
	// 	FIPv4Address IPAddress;
	// 	FIPv4Address::Parse(GAMA_IP, IPAddress);
	// 	FIPv4Endpoint Endpoint(IPAddress, TCP_PORT);

	// 	TcpSocket = FTcpSocketBuilder(TEXT("TcpSocket")).AsReusable().Build();
	// 	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	// 	if (TcpSocket -> Connect(*SocketSubsystem->CreateInternetAddr(Endpoint.Address.Value, Endpoint.Port)))
	// 	{
	// 		// Sends a message to gama to confirm it's connected
	// 		FString connection_str = FString("connected\n");
	// 		int32 BytesSent;
	// 		if (TcpSocket -> Send((const uint8*)  TCHAR_TO_ANSI(*connection_str), connection_str.Len(), BytesSent))
	// 		{
	// 			tcp_connected = true;
	// 		}
	// 	}
	// }

	// if (tcp_connected)
	// {
	// 	uint32 BufferSize;
	// 	FString message = "";
	// 	//we loop over everything that's pending to reconstitute the full message
	// 	while (TcpSocket->HasPendingData(BufferSize)) {
	// 		uint8* DataChunk = new uint8[BufferSize+1];
	// 		int32 BytesRead;
	// 		if (TcpSocket -> Recv(DataChunk, BufferSize, BytesRead) && BytesRead > 0)
	// 		DataChunk[BufferSize] = '\0'; // needs to add the end of string symbol
	// 		message += UTF8_TO_TCHAR(DataChunk);
	// 		delete[] DataChunk;
	// 	}

	// 	if (message != "") {
	// 		TSharedPtr<FJsonObject> MyJson;

	// 		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*message);

	// 		if (FJsonSerializer::Deserialize(Reader, MyJson))
	// 		{
	// 			UE_LOG(LogTemp, Display, TEXT("Received and deserialized: %s"), *message);
	// 			ObjHandler->HandleObject(MyJson, GetWorld());
	// 		}
	// 		else {
	// 			// The deserialization failed, handle this case
	// 			UE_LOG(LogTemp, Display, TEXT("Unable to deserialize because: %s Message: %s"), *Reader->GetErrorMessage(), *message);
	// 		}
	// 	}
	// }
}

void AGamaActions::SendChange(int type, int32 ID) const
{
	// FString change_msg = FString("{ \"type\": ") + FString::FromInt(type) + FString(", \"id\": ") + FString::FromInt(ID) + FString("}\n");
	// int32 BytesSent;
	// TcpSocket->Send((const uint8 *)TCHAR_TO_ANSI(*change_msg), change_msg.Len(), BytesSent);
}
