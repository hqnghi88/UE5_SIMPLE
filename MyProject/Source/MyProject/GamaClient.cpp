// Fill out your copyright notice in the Description page of Project Settings.

#include "GamaClient.h"
#include "GamaActions.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "Serialization/JsonSerializer.h"
#include "Containers/Array.h"
#include "ObjectHandler.h"
#include "Engine/World.h"
#include "ExpParameter.h"
#include <string>

GamaClient::GamaClient()
{
    _exp_id = 0;
    _socket_id = 0;
    this->message_handler = this;
}

GamaClient::GamaClient(AObjectHandler *objHdlr)
{
    _exp_id = 0;
    _socket_id = 0;
    ObjHandler=objHdlr;
    this->message_handler = this;
}

GamaClient::GamaClient(FString url, int32 port, AObjectHandler *objHdlr)
{
    _exp_id = 0;
    _socket_id = 0;
    const FString ServerURL = FString("ws://") + url + FString(":") + FString(std::to_string(port).c_str()); // Your server URL. You can use ws, wss or wss+insecure.
    const FString ServerProtocol = FString("ws");                                                            // The WebServer protocol you want to use
    Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);
    ObjHandler=objHdlr;
    this->message_handler = new GamaClient(objHdlr);
}

bool GamaClient::IsConnected() const
{
    return connected; // Socket->IsConnected();
}
bool GamaClient::IsPlaying() const
{
    return playing;
}

void GamaClient::SetConnected(bool b)
{
    connected = b;
}

void GamaClient::SetPlaying(bool b)
{
    playing = b;
}

void GamaClient::connect() const
{
    // We bind all available events
    Socket->OnConnected().AddLambda([this]() -> void
                                    {
                                        // This code will run once connected.
                                        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully!!! connected");
                                        if(message_handler){
                                            message_handler->SetConnected(true); 
                                        }
                                        UE_LOG(LogTemp, Display, TEXT("connected")); });

    Socket->OnConnectionError().AddLambda([](const FString &Error) -> void
                                          {
        // This code will run if the connection failed. Check Error to see what happened.
        UE_LOG(LogTemp, Display, TEXT("Something bad happened while trying to connect")); });

    Socket->OnClosed().AddLambda([](int32 StatusCode, const FString &Reason, bool bWasClean) -> void
                                 {
        // This code will run when the connection to the server has been terminated.
        // Because of an error or a call to Socket->Close().
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Connection closed");
        UE_LOG(LogTemp, Display, TEXT("Connection closed")); });

    Socket->OnMessage().AddLambda([&](const FString &Message) -> void
                                  {

        // This code will run when we receive a string message from the server.
        // UE_LOG(LogTemp, Display, TEXT("Message received: %s"), *FString(Message));

        TSharedPtr<FJsonObject> MyJson;

        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Message);

        if (FJsonSerializer::Deserialize(Reader, MyJson))
        {
            // The deserialization failed, handle this case
            // UE_LOG(LogTemp, Display, TEXT("Unable to deserialize"))
            if (MyJson->GetField<EJson::String>(FString("type")) -> Type != EJson::Null) {
                 message_handler->HandleCommand(MyJson);
            }
        } });

    Socket->OnRawMessage().AddLambda([](const void *Data, SIZE_T Size, SIZE_T BytesRemaining) -> void
                                     {
                                         // This code will run when we receive a raw (binary) message from the server.
                                     });

    Socket->OnMessageSent().AddLambda([](const FString &MessageString) -> void
                                      {
        // This code is called after we sent a message to the server.
        // UE_LOG(LogTemp, Display, TEXT("sent: %s"), *FString(MessageString)); 
        });

    // And we finally connect to the server.
    Socket->Connect();
}

void GamaClient::exit() const
{
    if (!connected) //! Socket->IsConnected())
    {
        return;
    }

    FString exit_command = FString("\
    {\
        \"type\": \"exit\"\
    }\n");

    Socket->Send(exit_command);
}

void GamaClient::load(int64 socket_id, FString file_path, FString experiment_name, bool console, bool status, bool dialog, TArray<ExpParameter *> parameters, FString end_condition) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        // Don't send if we're not connected.
        UE_LOG(LogTemp, Display, TEXT("Cannot load, not connected"));
        return;
    }

    FString params = FString("[");

    for (int i = 0; i < parameters.Num(); i++)
    {
        params += parameters[i]->Convert();
        if (i != parameters.Num() - 1)
        {
            params += FString(", ");
        }
    }

    params += FString("]");

    FString load_command = FString("\
    {\
        \"type\": \"load\",\
        \"socket_id\": \"") +
                           FString(std::to_string(socket_id).c_str()) + FString("\",\
        \"model\": \"") + file_path +
                           FString("\",\
        \"experiment\": \"") +
                           experiment_name + FString("\",\
        \"console\": ") + (console ? "true" : "false") +
                           FString(",\
        \"status\": ") + (status ? "true" : "false") +
                           FString(",\
        \"dialog\": ") + (dialog ? "true" : "false") +
                           FString(",\
        \"runtime\": ") + "false" +
                           FString(",\
        \"parameters\": ") +
                           params + FString(",\
        \"until\": \"") + end_condition +
                           FString("\"\
    }\n");

    Socket->Send(load_command);
}

void GamaClient::play(int64 socket_id, int32 exp_id, bool sync) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString play_command = FString("\
    {\
        \"type\": \"play\",\
        \"socket_id\": \"") +
                           FString(std::to_string(socket_id).c_str()) + FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                           FString("\",\
        \"sync\": ") + (sync ? "true" : "false") +
                           FString("\
    }");

    Socket->Send(play_command);
}

void GamaClient::pause(int64 socket_id, int32 exp_id) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString pause_command = FString("\
    {\
        \"type\": \"pause\",\
        \"socket_id\": \"") +
                            FString(std::to_string(socket_id).c_str()) + FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                            FString("\"\
    }");

    Socket->Send(pause_command);
}

void GamaClient::step(int64 socket_id, int32 exp_id, int32 steps, bool sync) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString step_command = FString("\
    {\
        \"type\": \"step\",\
        \"socket_id\": \"") +
                           FString(std::to_string(socket_id).c_str()) + FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                           FString("\",\
        \"nb_step\": ") + FString(std::to_string(steps).c_str()) +
                           FString(",\
        \"sync\": ") + (sync ? "true" : "false") +
                           FString("\
    }");

    Socket->Send(step_command);
}

void GamaClient::stepBack(int64 socket_id, int32 exp_id, int32 steps, bool sync) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString step_command = FString("\
    {\
        \"type\": \"stepBack\",\
        \"socket_id\": \"") +
                           FString(std::to_string(socket_id).c_str()) + FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                           FString("\",\
        \"nb_step\": ") + FString(std::to_string(steps).c_str()) +
                           FString(",\
        \"sync\": ") + (sync ? "true" : "false") +
                           FString("\
    }");

    Socket->Send(step_command);
}

void GamaClient::stop(int64 socket_id, int32 exp_id) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString stop_command = FString("\
    {\
        \"type\": \"stop\",\
        \"socket_id\": \"") +
                           FString(std::to_string(socket_id).c_str()) + FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                           FString("\"\
    }");

    Socket->Send(stop_command);
}

void GamaClient::reload(int64 socket_id, int32 exp_id, TArray<ExpParameter *> parameters, FString end_condition) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString params = FString("[");

    for (int i = 0; i < parameters.Num(); i++)
    {
        params += parameters[i]->Convert();
    }

    params += FString("]");

    FString reload_command = FString("\
    {\
        \"type\": \"reload\",\
        \"socket_id\": \"") + FString(std::to_string(socket_id).c_str()) +
                             FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                             FString("\",\
        \"params\": ") + params +
                             FString(",\
        \"until\": \"") + end_condition +
                             FString("\"\
    }");

    Socket->Send(reload_command);
}

void GamaClient::expression(int64 socket_id, int32 exp_id, FString expr, bool esc) const
{
    if (!message_handler->connected) //! Socket->IsConnected())
    {
        return;
    }

    FString expression_command = FString("\
    {\
        \"type\": \"expression\",\
        \"socket_id\": \"") + FString(std::to_string(socket_id).c_str()) +
                                 FString("\",\
        \"exp_id\": \"") + FString(std::to_string(exp_id).c_str()) +
                                 FString("\",\
        \"expr\": \"") + expr + FString("\",\
        \"escaped\": \"") + (esc ? "true" : "false") + FString("\",\
    }");

    Socket->Send(expression_command);

    // Socket->OnMessage().Clear();
    // Socket->OnMessage().AddLambda([&](const FString & Message) -> void {
    //     // This code will run when we receive a string message from the server.
    //     UE_LOG(LogTemp, Display, TEXT("Message received: %s"), *FString(Message));

    //     TSharedPtr<FJsonObject> MyJson;

    //     TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Message);

    //     if (FJsonSerializer::Deserialize(Reader, MyJson))
    //     {
    //         // The deserialization failed, handle this case
    //         // UE_LOG(LogTemp, Display, TEXT("Unable to deserialize"))
    //         if (MyJson->GetField<EJson::String>(FString("type")) -> Type != EJson::Null) {
    //             // message_handler -> HandleCommand(act_name, MyJson);

    //     // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "2connected");
    //         }
    //     }
    // });
}

void GamaClient::HandleCommand(TSharedPtr<FJsonObject> MyJson)
{
    // FHttpResponsePtr Response;
    FString type;

    if (MyJson->TryGetStringField("type", type))
    {
        type = MyJson->GetStringField("type");
        if (type == "ConnectionSuccessful")
        {
            HandleConnectionSuccessful(MyJson);
        }
        else if (type == "CommandExecutedSuccessfully")
        {
            HandleCommandExecutedSuccessfully(MyJson);
        }
    }
}

int32 GamaClient::GetExpId() const
{
    return _exp_id;
}

void GamaClient::SetExpId(int64 ee)
{
    _exp_id = ee;
}
int64 GamaClient::GetSocketId() const
{
    return _socket_id;
}

void GamaClient::SetSocketId(int64 ss)
{
    _socket_id = ss;
}

void GamaClient::HandleConnectionSuccessful(TSharedPtr<FJsonObject> MyJson)
{
    int64 _socket_id1;
    if (MyJson->TryGetNumberField("content", _socket_id1))
    {
        _socket_id1 = MyJson->GetIntegerField("content");
        message_handler->SetSocketId(_socket_id1);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "socket_id");
    }
}

void GamaClient::HandleCommandExecutedSuccessfully(TSharedPtr<FJsonObject> MyJson)
{
    // const TSharedPtr<FJsonObject>* Content;
    int OutNumber;

    if (message_handler->GetExpId() == 0 && MyJson->TryGetNumberField("content", OutNumber))
    {
        message_handler->SetExpId(OutNumber);
    }
    // const TSharedPtr<FJsonObject> *bbb;
    // FString ttt;
    // if (MyJson->TryGetStringField("content", ttt))
    // {
    //     // FString ttt;
    //     // (*bbb)->TryGetStringField("type", ttt);
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(TEXT("content ")) + ttt);
    //     // FString ttt;
    //     // (*BuildingInfo)->TryGetStringField("type", ttt);
    // }
    const TSharedPtr<FJsonObject> *Command;
    if (MyJson->TryGetObjectField("command", Command))
    {
        FString CommandName;
        if ((*Command)->TryGetStringField("type", CommandName) && CommandName.Equals("play"))
        {
            if (message_handler)
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "playing");
                message_handler->SetPlaying(true);
            }
        }
        // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, CommandName);
        if ((*Command)->TryGetStringField("type", CommandName) && CommandName.Equals("expression"))
        {
            //     const TSharedPtr<FJsonObject> *BuildingInfo;

            //     if (MyJson->TryGetObjectField("content", BuildingInfo))
            //     {
                
                // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "sssss");
            ObjHandler->HandleObject(MyJson); 
            //         // FString ttt;
            //         // (*BuildingInfo)->TryGetStringField("type", ttt);
            //     }
        }
    }
}
GamaClient::~GamaClient()
{
    Socket->Close();
}
