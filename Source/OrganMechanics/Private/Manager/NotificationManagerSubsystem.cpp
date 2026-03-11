// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/NotificationManagerSubsystem.h"

void UNotificationManagerSubsystem::AddNotification(ENotificationType _NotificationType, FString _NotificationText)
{
	OnNotificationAdded.Broadcast(_NotificationType, _NotificationText);
}

void UNotificationManagerSubsystem::RemoveNotification(ENotificationType _NotificationType, FString _NotificationText)
{
	OnNotificationRemoved.Broadcast(_NotificationType, _NotificationText);
}
