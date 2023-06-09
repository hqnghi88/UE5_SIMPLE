// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectHandler.h"
#include "Building.h"
#include "House.h"
#include "EmptyBuilding.h"
#include "Office.h"
#include "People.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Containers/Array.h"
#include "Engine/World.h"
#include "WebSocketTestGameInstance.h"
#include "GamaActions.h"
#include "GamaMap.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>

// Sets default values
AObjectHandler::AObjectHandler()
{
	/*house_ids = {};
	empty_ids = {};
	office_ids = {};
	people_ids = {};

	scaling_factor = 500;
	x_offset = -30000;
	y_offset = -50000;

	houses = {};
	empty_buildings = {};
	offices = {};
	peoples = {};*/
}

// bool AObjectHandler::id_found(int32 ID, TArray<int32> ids)
//{
//	return ids.Find(ID) >= 0;
// }
//
// TArray<int32> AObjectHandler::GetHouseIds()
//{
//	return house_ids;
// }
//
// TArray<int32> AObjectHandler::GetEmptyIds()
//{
//	return empty_ids;
// }
//
// TArray<int32> AObjectHandler::GetOfficeIds()
//{
//	return office_ids;
// }
//
// TArray<int32> AObjectHandler::GetPeopleIds()
//{
//	return people_ids;
// }
//
// TArray<AHouse*> AObjectHandler::GetHouses()
//{
//	return houses;
// }
//
// TArray<AEmptyBuilding*> AObjectHandler::GetEmptyBuildings()
//{
//	return empty_buildings;
// }
//
// TArray<AOffice*> AObjectHandler::GetOffices()
//{
//	return offices;
// }
//
// TArray<APeople*> AObjectHandler::GetPeoples()
//{
//	return peoples;
// }

void AObjectHandler::HandleObject(TSharedPtr<FJsonObject> MyJson)
{
	TSharedPtr<FJsonObject> CmdObject = MyJson->GetObjectField("command");
	FString actname = CmdObject->GetStringField("actname");
	// GLog->Log("Type:" + actname);
	if (actname == "BBox")
	{

		TSharedPtr<FJsonObject> JsonObject = MyJson;
		TSharedPtr<FJsonObject> PersonObject = JsonObject->GetObjectField("content");

		// GLog->Log("Type:" + PersonObject->GetStringField("type"));

		// Retrieving an array property and printing each field
		TArray<TSharedPtr<FJsonValue>> objArray = PersonObject->GetArrayField("features");
		for (int32 index = 0; index < objArray.Num(); index++)
		{
			FString test = objArray[index]->AsObject()->GetObjectField("properties")->GetStringField("location");
			std::string exampleString = std::string(TCHAR_TO_UTF8(*test));

			exampleString.front() = exampleString.back() = ' ';
			std::replace(exampleString.begin(), exampleString.end(), ',', ' ');

			// Create stringstream from string.
			auto iss = std::istringstream(exampleString);

			// Create vector of doubles from stringstream.
			const auto doublesVector = std::vector<double>(std::istream_iterator<double>(iss),
														   std::istream_iterator<double>());
			// FVector fv=new FVector(doublesVector[0],doublesVector[1],doublesVector[2]);
			// GLog->Log(FString(std::to_string(doublesVector[0]).c_str()));
			// for (const auto d : doublesVector)
			// {
			// }
			int iid = objArray[index]->AsObject()->GetIntegerField("id");
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "error map");
			gamamap->InitOrUpdatePeople(iid, doublesVector[0], doublesVector[1], doublesVector[2], doublesVector[0], GetWorld());
		}
	}

	if (actname == "predator")
	{

		TSharedPtr<FJsonObject> JsonObject = MyJson;
		TSharedPtr<FJsonObject> PersonObject = JsonObject->GetObjectField("content");

		// GLog->Log("Type:" + PersonObject->GetStringField("type"));

		// Retrieving an array property and printing each field
		TArray<TSharedPtr<FJsonValue>> objArray = PersonObject->GetArrayField("features");
		for (int32 index = 0; index < objArray.Num(); index++)
		{
			FString test = objArray[index]->AsObject()->GetObjectField("properties")->GetStringField("location");
			std::string exampleString = std::string(TCHAR_TO_UTF8(*test));

			exampleString.front() = exampleString.back() = ' ';
			std::replace(exampleString.begin(), exampleString.end(), ',', ' ');

			// Create stringstream from string.
			auto iss = std::istringstream(exampleString);

			// Create vector of doubles from stringstream.
			const auto doublesVector = std::vector<double>(std::istream_iterator<double>(iss),
														   std::istream_iterator<double>());
			// FVector fv=new FVector(doublesVector[0],doublesVector[1],doublesVector[2]);
			// GLog->Log(FString(std::to_string(doublesVector[0]).c_str()));
			// for (const auto d : doublesVector)
			// {
			// }
			int iid = objArray[index]->AsObject()->GetIntegerField("id");
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "error map");
			gamamap->InitOrUpdatePredator(iid, doublesVector[0], doublesVector[1], doublesVector[2], doublesVector[0], GetWorld());
		}
	}
	// 	const TArray<TSharedPtr<FJsonValue>> *BuildingInfo;
	// 	const TArray<TSharedPtr<FJsonValue>> *PeopleInfo;

	// 	if (MyJson->TryGetArrayField("building", BuildingInfo))
	// 	{
	// 		HandleBuilding(BuildingInfo);
	// 	}

	// 	if (MyJson->TryGetArrayField("people", PeopleInfo))
	// 	{
	// 		HandlePeople(PeopleInfo);
	// 	}
}

void AObjectHandler::HandleBuilding(const TArray<TSharedPtr<FJsonValue>> *&Info)
{
	// we update the visibility of buildings
	// for (int32 i = 0; i < Info->Num(); i++)
	// {
	// 	int type = (*Info)[i]->AsNumber();
	// 	gamamap->SetBuildingVisible((ABuilding::BuildingTypes)type, i);
	// }
}

void AObjectHandler::HandlePeople(const TArray<TSharedPtr<FJsonValue>> *&Info)
{
	TSet<int> ids;
	// Start by updating and/or creating people in the simulation
	for (int i = 0; i < Info->Num(); i++)
	{
		TArray<TSharedPtr<FJsonValue>> obj = (*Info)[i]->AsArray();
		int32 id = obj[0]->AsNumber();
		int32 x = obj[1]->AsNumber();
		int32 y = obj[2]->AsNumber();
		int32 z = obj[3]->AsNumber();
		int32 heading = obj[4]->AsNumber();
		gamamap->InitOrUpdatePeople(id, x, y, z, heading, CurrentWorld);
		ids.Add(id);
	}
	// Remove absent people
	// TArray<int> old_people_ids = map->GetPeopleIds(); // we explicitly make a copy
	// for (int id : gamamap->GetPeopleIds())
	// {
	// 	if (!ids.Contains(id))
	// 	{
	// 		// map->RemovePeople(id);
	// 	}
	// }
}

AObjectHandler::~AObjectHandler()
{
	delete gamamap;
}

// Called when the game starts or when spawned
void AObjectHandler::BeginPlay()
{
	Super::BeginPlay();
	gamamap->Init(CurrentWorld);
}

void AObjectHandler::EndPlay(const EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
}

// Called every frame
void AObjectHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
