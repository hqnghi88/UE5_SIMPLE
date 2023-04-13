// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"

#include "GamaClient.h"
#include "GamaActionsMessageHandler.h" 
#include "WebSocketTestGameInstance.generated.h"
/**
 *
 */
UCLASS()
class MYPROJECT_API UWebSocketTestGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// Connection constants
	const FString GAMA_URL		= "localhost";
	const FString GAMA_IP		= "127.0.0.1";
	const int GAMA_SERVER_PORT	= 6868;
	const uint16 TCP_PORT		= 8000;

	//Gama server handling
	GamaClient* client;
	GamaActionsMessageHandler* message_handler;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	TSharedPtr<IWebSocket> WebSocket;

};