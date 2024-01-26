// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSphereLegends/Public/EOS_PlayerController.h"

#include "BattleSphereLegends/Public/EOS_GameMode.h"


void AEOS_PlayerController::OnNetCleanup(UNetConnection* Connection)
{
	UE_LOG(LogTemp, Warning, TEXT("OnNetCleanup Success 1...................................................."));
	
	AEOS_GameMode* GameMode = Cast<AEOS_GameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->PreLogout(this);
		UE_LOG(LogTemp, Warning, TEXT("OnNetCleanup Success 2...................................................."));
	}

	Super::OnNetCleanup(Connection);
	UE_LOG(LogTemp, Warning, TEXT("OnNetCleanup Success 3...................................................."));
}
