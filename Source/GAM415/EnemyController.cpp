// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Enemy.h"

AEnemyController::AEnemyController(FObjectInitializer const& ObjectInitializer)
{
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// if selected pawn in in the enemy class
	if (AEnemy* const enemy = Cast<AEnemy>(InPawn))
	{
		// get tree used by the enemy, uses getter funtion set inside Enemy.h
		if (UBehaviorTree* const bTree = enemy->GetBehaviorTree())
		{
			// temp local BB component
			UBlackboardComponent* bb;
			// causes the enemy to use the bTree BB in Enemy.h
			// Basically, tries to access the BB asset from within the class
			// if it exists, puts it inside the variable bb
			UseBlackboard(bTree->BlackboardAsset, bb);
			// reassigns the BB for this class as the one from Enemy.h
			Blackboard = bb;
			// starts running the behavior tree
			RunBehaviorTree(bTree);
		}
	}
}
