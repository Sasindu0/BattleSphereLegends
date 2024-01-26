// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSphereLegends/Public/EOS_GameMode.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlinesessionInterface.h"

void AEOS_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		FUniqueNetIdRepl UniqueNetIdRepl;
		if (NewPlayer->IsLocalController())
		{
			ULocalPlayer* LocalPlayerRef = NewPlayer->GetLocalPlayer();
			if(LocalPlayerRef)
			{
				UniqueNetIdRepl = LocalPlayerRef->GetPreferredUniqueNetId();
			}
			else
			{
				UNetConnection* RemoteNetConnectionRef = Cast<UNetConnection>(NewPlayer->Player);
				check(IsValid(RemoteNetConnectionRef));
				UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
			}
		}
		else
		{
			UNetConnection* RemoteNetConnectionRef = Cast<UNetConnection>(NewPlayer->Player);
			check(IsValid(RemoteNetConnectionRef));
			UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
		}

		TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
		check(UniqueNetId != nullptr);
		IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(NewPlayer->GetWorld());
		IOnlineSessionPtr SessionRef = SubsystemRef->GetSessionInterface();
		bool bRegistrationSuccess = SessionRef->RegisterPlayer(FName("MainSession"),*UniqueNetId,false);


		if(bRegistrationSuccess)
		{
			UE_LOG(LogTemp,Warning,TEXT("Registration Success"));
		}

	}

}

void AEOS_GameMode::PreLogout(APlayerController* ExitingPlayer)
{
	if (ExitingPlayer)
	{
		FUniqueNetIdRepl UniqueNetIdRepl;
		if (ExitingPlayer->IsLocalController())
		{
			ULocalPlayer* LocalPlayerRef = ExitingPlayer->GetLocalPlayer();
			if(LocalPlayerRef)
			{
				UniqueNetIdRepl = LocalPlayerRef->GetPreferredUniqueNetId();
			}
			else
			{
				UNetConnection* RemoteNetConnectionRef = Cast<UNetConnection>(ExitingPlayer->Player);
				check(IsValid(RemoteNetConnectionRef));
				UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
			}
		}
		else
		{
			UNetConnection* RemoteNetConnectionRef = Cast<UNetConnection>(ExitingPlayer->Player);
			check(IsValid(RemoteNetConnectionRef));
			UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
		}

		TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
		check(UniqueNetId != nullptr);
		IOnlineSubsystem* SubsystemRef = Online::GetSubsystem(ExitingPlayer->GetWorld());
		IOnlineSessionPtr SessionRef = SubsystemRef->GetSessionInterface();
		SessionRef->ClearOnUnregisterPlayersCompleteDelegates(this);
		bool bUnregistrationSuccess = SessionRef->UnregisterPlayer(FName("MainSession"),*UniqueNetId);

		UE_LOG(LogTemp,Warning,TEXT("Unregistration Success2!!!"));


		if(bUnregistrationSuccess)
		{
			UE_LOG(LogTemp,Warning,TEXT("Unregistration Success1!!!"));
		}

	}
}
