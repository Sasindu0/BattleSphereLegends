// Fill out your copyright notice in the Description page of Project Settings.

#include "EOS_GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"

void UEOS_GameInstance::LoginWithEOS(FString ID, FString Token, FString LoginType)
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();

		if (IdentityPointerRef)
		{
			FOnlineAccountCredentials AccountDetails;

			AccountDetails.Id = ID;
			AccountDetails.Token = Token;
			AccountDetails.Type = LoginType;

			

			IdentityPointerRef->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::LoginWithEOS_Return);
			IdentityPointerRef->Login(0, AccountDetails);
			
		}
	}
}

FString UEOS_GameInstance::GetPlayerUsername()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();

		if (IdentityPointerRef)
		{
			if (IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn)
			{
				return IdentityPointerRef->GetPlayerNickname(0);
			}
		}
	}

	return FString();
}

bool UEOS_GameInstance::IsLoggedIn()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();

		if (IdentityPointerRef)
		{
			if (IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn)
			{
				return true;
			}
		}
	}

	return false;
}

void UEOS_GameInstance::CreateEOSSession(bool bIsDedicatedServer, bool bIsLanServer, int32 NumberOfPublicConnections)
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if (SessionPtrRef)
		{
			
			FOnlineSessionSettings SessionCreationInfo;

			SessionCreationInfo.bIsDedicated = bIsDedicatedServer;
			SessionCreationInfo.bIsLANMatch = bIsLanServer;
			SessionCreationInfo.bAllowInvites = true;
			SessionCreationInfo.NumPublicConnections = NumberOfPublicConnections;
			SessionCreationInfo.bUseLobbiesIfAvailable = false;
			SessionCreationInfo.bUsesPresence = true;
			SessionCreationInfo.bShouldAdvertise = true;

			SessionCreationInfo.Set(SEARCH_KEYWORDS, FString("RandomHi"), EOnlineDataAdvertisementType::ViaOnlineService);
			SessionPtrRef->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnCreateSessionCompleted);
			SessionPtrRef->CreateSession(0, FName("MainSession"), SessionCreationInfo);
			
		}
	}
}

void UEOS_GameInstance::FindAndJoinSession()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if (SessionPtrRef)
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->bIsLanQuery = false;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->QuerySettings.SearchParams.Empty();
			SessionPtrRef->OnFindSessionsCompleteDelegates.AddUObject(this,&UEOS_GameInstance::OnFindSessionCompleted);
			SessionPtrRef->FindSessions(0,SessionSearch.ToSharedRef());

			if (SessionPtrRef)
			{
				UE_LOG(LogTemp, Warning, TEXT("Find Success"));
			}
		}
	}
}

void UEOS_GameInstance::JoinSession()
{
}

void UEOS_GameInstance::DestroySession()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy Success0"));
	
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy Success1"));
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if (SessionPtrRef)
		{
			UE_LOG(LogTemp, Warning, TEXT("Destroy Success2"));
			SessionPtrRef->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnDeleteSessionCompleted);
			
			SessionPtrRef->DestroySession(FName("MainSession"));
			UE_LOG(LogTemp, Warning, TEXT("Destroy Success3"));
		}
	}
}

void UEOS_GameInstance::ClearOnCreateSession()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if (SessionPtrRef)
		{
			SessionPtrRef->ClearOnCreateSessionCompleteDelegates(this);
			SessionPtrRef->ClearOnDestroySessionCompleteDelegates(this);
		}
	}
}

void UEOS_GameInstance::ClearOnSession()
{
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if (SessionPtrRef)
		{
			SessionPtrRef->ClearOnFindSessionsCompleteDelegates(this);
			SessionPtrRef->ClearOnJoinSessionCompleteDelegates(this);
		}
	}
}


void UEOS_GameInstance::LoginWithEOS_Return(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserId, const FString& Error)
{
	if (bWasSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login Success!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Login Failed: %S"), *Error);
	}
}

void UEOS_GameInstance::OnCreateSessionCompleted(FName SessionName, bool bWasSuccess)
{
	if (bWasSuccess)
	{
		GetWorld()->ServerTravel(OpenLevelText);

		UE_LOG(LogTemp, Warning, TEXT("Create Session Success"));
	}
	
}

void UEOS_GameInstance::OnDeleteSessionCompleted(FName SessionName, bool bWasSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy Success0"));
	IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
	if (SubsystemRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy Success1"));
		IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
		if (SessionPtrRef)
		{
			UE_LOG(LogTemp, Warning, TEXT("Destroy Success2"));
			SessionPtrRef->ClearOnDestroySessionCompleteDelegates(this);
		}
	}
}

void UEOS_GameInstance::OnFindSessionCompleted(bool bWasSuccess)
{
	if(bWasSuccess)
	{
		IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
		if (SubsystemRef)
		{
			IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
			if (SessionPtrRef)
			{
				
				if(SessionSearch->SearchResults.Num()>0)
				{
					SessionPtrRef->OnJoinSessionCompleteDelegates.AddUObject(this,&UEOS_GameInstance::OnJoinSessionCompleted);
					SessionPtrRef->JoinSession(0,FName("MainSession"),SessionSearch->SearchResults[0]);
				}
				else
				{
					CreateEOSSession(false,false,5);
				}
			}
		}
	}
	else
	{
		CreateEOSSession(false,false,5);
	}
}

void UEOS_GameInstance::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if(Result == EOnJoinSessionCompleteResult::Success)
	{
		if(APlayerController *PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(),0))
		{
			FString JoinAddress;
			IOnlineSubsystem *SubsystemRef = Online::GetSubsystem(this->GetWorld());
			if (SubsystemRef)
			{
				IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
				if (SessionPtrRef)
				{
					SessionPtrRef->GetResolvedConnectString(FName("MainSession"),JoinAddress);
					UE_LOG(LogTemp,Warning,TEXT("Join Address: %s"), *JoinAddress);
					
					if(!JoinAddress.IsEmpty())
					{
						PlayerControllerRef->ClientTravel(JoinAddress,TRAVEL_Absolute);
					}
				}
			}
		}
	}
}


