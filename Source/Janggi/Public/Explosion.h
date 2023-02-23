// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class JANGGI_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_Explosion();
	UFUNCTION(BlueprintImplementableEvent)
		void BP_Attack();
};
