// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "People.h"
#include "Predator.h" 



/**
 * 
 */
class MYPROJECT_API GamaMap
{

protected:

	// Items lists 
	TMap<int, APeople*>		People;
	TMap<int, APredator*>		Predator;

	// Transformation parameters to scale to the world coordinates
	const int32 scaling_factor	= 1;
	const int32 x_offset		= 0;
	const int32 y_offset		= 0;
	const int32 z_offset		= 0;


public:


	GamaMap();

	void Init(UWorld* CurrentWorld);

	void InitOrUpdatePeople(int id, double x, double y, double z, double heading, UWorld* CurrentWorld);
	void RemovePeople(int id);
	void InitOrUpdatePredator(int id, double x, double y, double z, double heading, UWorld* CurrentWorld);
	void RemovePredator(int id); 

	inline APeople* GetPeople(int id) const {
		if (!People.Contains(id)) {
			return nullptr;
		}
		return People[id];
	}
	
	inline TArray<int> GetPeopleIds() const {
		TArray<int> out;
		People.GenerateKeyArray(out);
		return out;
	}

	inline TArray<APeople*> GetPeople() const {
		TArray<APeople*> out;
		People.GenerateValueArray(out);
		return out;
	}


	inline APredator* GetPredator(int id) const {
		if (!Predator.Contains(id)) {
			return nullptr;
		}
		return Predator[id];
	}
	
	inline TArray<int> GetPredatorIds() const {
		TArray<int> out;
		Predator.GenerateKeyArray(out);
		return out;
	}

	inline TArray<APredator*> GetPredator() const {
		TArray<APredator*> out;
		Predator.GenerateValueArray(out);
		return out;
	}


	~GamaMap();
};
