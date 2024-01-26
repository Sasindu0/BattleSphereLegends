// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EOS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESPHERELEGENDS_API AEOS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void PreLogout(APlayerController* ExitingPlayer);
	
};
