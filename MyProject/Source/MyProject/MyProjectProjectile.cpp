// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "People.h"
#include "Predator.h"
#include "WebSocketTestGameInstance.h"
#include <string>
AMyProjectProjectile::AMyProjectProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyProjectProjectile::OnHit); // set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AMyProjectProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) // && OtherComp->IsSimulatingPhysics()
	{

		// GLog->Log(FString(std::to_string(new_y).c_str()));
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ((UPrimitiveComponent *)OtherComp)->GetDetailedInfo());
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(std::to_string(((UPrimitiveComponent *)OtherComp)->GetComponentLocation()[0]).c_str()));
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			Destroy();
		}

		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(std::to_string(((APeople *)OtherComp)->GetID()).c_str()));

		if (OtherActor->GetClass()->IsChildOf(APeople::StaticClass()))
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ((APeople *)OtherActor)->GetID());
			((APeople *)OtherActor)->End();
			Destroy();
		}else
		if (OtherActor->GetClass()->IsChildOf(APredator::StaticClass()))
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ((APeople *)OtherActor)->GetID());
			((APredator *)OtherActor)->End();
			Destroy();
		}
		// UWebSocketTestGameInstance* GameInstance = Cast<UWebSocketTestGameInstance>(GetGameInstance());

		// if (GameInstance)
		// {
		// 	if (GameInstance->WebSocket->IsConnected())
		// 	{
		// 		GameInstance->WebSocket->Send("Hit "+((UPrimitiveComponent*)OtherComp)->GetDetailedInfo());
		// 	}
		// }
	}
}