// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlinesessionInterface.h"
#include "EOS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESPHERELEGENDS_API UEOS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(Blueprintcallable, Category="EOS Functions")
	void LoginWithEOS(FString ID, FString Token, FString LoginType);

	UFUNCTION(Blueprintcallable, BlueprintPure, Category = "EOS Functions")
	FString GetPlayerUsername();

	UFUNCTION(Blueprintcallable, BlueprintPure, Category = "EOS Functions")
	bool IsLoggedIn();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void CreateEOSSession(bool bIsDedicatedServer, bool bIsLanServer, int32 NumberOfPublicConnections);

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void FindAndJoinSession();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void JoinSession();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void DestroySession();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void ClearOnCreateSession();
	
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void ClearOnSession();
	
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EOS Variables")
	FString OpenLevelText;

	void LoginWithEOS_Return(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserId, const FString& Error);
	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccess);
	void OnDeleteSessionCompleted(FName SessionName, bool bWasSuccess);
	void OnFindSessionCompleted(bool bWasSuccess);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
};
