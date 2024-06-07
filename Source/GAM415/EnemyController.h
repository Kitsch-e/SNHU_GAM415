// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GAM415_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AEnemyController(FObjectInitializer const& ObjectInitializer);

protected:
	// runs when the controller possesses the character
	virtual void OnPossess(APawn* InPawn) override;
};
