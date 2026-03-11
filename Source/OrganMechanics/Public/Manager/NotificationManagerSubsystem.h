// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonEnums.h"
#include "Subsystems/WorldSubsystem.h"
#include "NotificationManagerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNotificationChanged, ENotificationType, NotificationType, FString, NotificationText);

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UNotificationManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AddNotification(ENotificationType _NotificationType, FString _NotificationText);

	UFUNCTION(BlueprintCallable)
	void RemoveNotification(ENotificationType _NotificationType, FString _NotificationText);

	UPROPERTY(BlueprintAssignable)
	FOnNotificationChanged OnNotificationAdded;

	UPROPERTY(BlueprintAssignable)
	FOnNotificationChanged OnNotificationRemoved;
	
};
