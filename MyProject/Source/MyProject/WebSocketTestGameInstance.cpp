// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketTestGameInstance.h"
#include "WebSocketsModule.h"

#include "GamaActions.h"
#include "GamaClient.h" 
#include "ExpParameter.h" 
#include "Math/Vector.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h" 
void UWebSocketTestGameInstance::Init()
{
	Super::Init();

    // Making sure that modules are loaded before using them
    if (!FModuleManager::Get().IsModuleLoaded("Websockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }
    if (!FModuleManager::Get().IsModuleLoaded("Json"))
    {
        FModuleManager::Get().LoadModule("Json");
    }
 
	client = new GamaClient(GAMA_URL, GAMA_SERVER_PORT);
	client -> connect();
	// //ObjHandler = new ObjectHandler();

	// // Spawn an instance of ObjectHandlerr in the map in a place far from the objects
	// UWorld* CurrentWorld = GetWorld();
	// const FVector* Loc = new FVector(-1000, -1000, -1000);
	// ObjHandler = (AObjectHandler*)CurrentWorld->SpawnActor(AObjectHandler::StaticClass(), Loc);

	// // read the model
	// if (first && message_handler -> GetSocketId() > 0)
	// {
	// 	FString current_path = FPaths::ProjectDir();
	// 	FString url = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead( *(current_path + "../MobilityModel/models/Grid Model.gaml"));
	// 	FString model = "grid_model";
	// 	client -> load(message_handler -> GetSocketId(), url, model);
	// 	first = false;
	// }

	// // play command
	// if(!played && message_handler -> GetExpId() > 0)
	// {
	// 	client -> play(message_handler -> GetSocketId(), message_handler -> GetExpId(), true);
	// 	played = true;
	// }
	
	// Connects to TCP server
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

	// WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://localhost:6868");

	// WebSocket->OnConnected().AddLambda([]()
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully!!! connected");
	// 	});

	// WebSocket->OnConnectionError().AddLambda([](const FString& Error)
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
	// 	});

	// WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
	// 	});

	// WebSocket->OnMessage().AddLambda([](const FString& MessageString)
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);
	// 	});

	// WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
	// 	{
	// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);
	// 	});

	// WebSocket->Connect();
}

void UWebSocketTestGameInstance::Shutdown()
{
	
	// GetWorld()->DestroyActor(ObjHandler);
	// delete message_handler;
	client->stop(client->GetSocketId(), client->GetExpId()); 
	delete client;
	// // if (WebSocket->IsConnected())
	// // {
	// // 	WebSocket->Close();
	// // }
	Super::Shutdown();
}