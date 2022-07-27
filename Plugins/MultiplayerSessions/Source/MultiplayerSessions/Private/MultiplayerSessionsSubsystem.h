// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	/*
		To handle session functionality. The Menu class will call these.
	*/
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void DestroySession();
	void StartSession();

protected:

	/*
		Internal callbacks to the delegates we'll add to the Online SessionInterface delegate list.
		This don't need to be called outside this class.
	*/
	void OnCreateSessionComplete(FName SessionName, bool bWalSuccessful);
	void OnFindSessionComplete(bool bWalSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWalSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWalSuccessful);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	/*
		To add to the Online Session Interface delegate list.
		We'll bind our MultiplayerSessionSubsystem internal callbacks to these.
	*/
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;
};
