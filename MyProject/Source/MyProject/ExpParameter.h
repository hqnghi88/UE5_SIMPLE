// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MYPROJECT_API ExpParameter
{
private:
	// Properties of experiment parameters
	FString type;
	FString value;
	FString name;
public:
	ExpParameter();
	ExpParameter(FString Type, FString Value, FString Name);

	// Convert the list of parameters into a string message
	FString Convert() const;

	~ExpParameter();
};
