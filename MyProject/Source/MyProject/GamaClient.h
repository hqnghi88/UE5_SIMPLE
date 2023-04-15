// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"
#include "Containers/Array.h" 
#include "ExpParameter.h"


class MYPROJECT_API GamaClient
{
private: 
	TSharedPtr<IWebSocket> Socket; 
	GamaClient* message_handler; 
public:
	int32 _exp_id;
	int64 _socket_id;
	bool playing = false;
public:
	GamaClient();
	GamaClient(FString url, int32 port);
	void connect() const;
	bool IsConnected() const;
	bool IsPlaying() const;


	// Get simulation parameters
	int32 GetExpId() const;
	int64 GetSocketId() const;
	void SetSocketId(int64 ss);
	// Handle commands returned by Json messages
	void HandleCommand( TSharedPtr<FJsonObject> MyJson);
	void HandleConnectionSuccessful(TSharedPtr<FJsonObject> MyJson);
	void HandleCommandExecutedSuccessfully(  TSharedPtr<FJsonObject> MyJson);

	// basic Gama server commands
	void exit() const;
	void load(int64 socket_id, FString file_path, FString experiment_name, bool console = true, bool status = false, bool dialog = false, TArray<ExpParameter*> parameters = TArray<ExpParameter*>(), FString end_condition = "") const;
	void play(int64 socket_id, int32 exp_id, bool sync = false) const;
	void pause(int64 socket_id, int32 exp_id) const;
	void step(int64 socket_id, int32 exp_id, int32 steps = 1, bool sync = false) const;
	void stepBack(int64 socket_id, int32 exp_id, int32 steps = 1, bool sync = false) const;
	void stop(int64 socket_id, int32 exp_id) const;
	void reload(int64 socket_id, int32 exp_id, TArray<ExpParameter*> parameters = TArray<ExpParameter*>(), FString end_condition = "") const;
	// void expression(int64 socket_id, int32 exp_id, FString expr) const;
	void expression(int64 socket_id, int32 exp_id, FString expr, FString act_name) const;

	virtual ~GamaClient();
};
