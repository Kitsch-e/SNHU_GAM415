// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "EnemyController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	// name of this task within the editor
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller and enemy
	if (AEnemyController* const controller = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = controller->GetPawn())
		{
			// get the enemy's location
			auto const originalLocation = enemy->GetActorLocation();

			// get the navigation system and generate a new location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation newLocation;
				if (NavSys->GetRandomPointInNavigableRadius(originalLocation, searchRadius, newLocation))
				{
					// sets the key within BB to the new location
					//OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), newLocation.Location);
					//OwnerComp.GetBlackboardComponent();
				}

				// finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}