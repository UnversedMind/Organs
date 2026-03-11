// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/BlueprintExtenderFunctionLibrary.h"
#include "MediaPlayer.h"

FString UBlueprintExtenderFunctionLibrary::ConvertCamelCaseToSpaces(FString _InputString)
{
	FString returnString;
	const TArray<TCHAR> charArray = _InputString.GetCharArray();
	for (int i = 0; i < charArray.Num(); i++) 
	{
		if (i == 0)
		{
			returnString.AppendChar(charArray[i]);
			continue;
		}
		if (FChar::IsUpper(charArray[i]))
		{
			returnString.AppendChar(*UTF8_TO_TCHAR(" "));
		}
		returnString.AppendChar(charArray[i]);
	}
	return returnString;
}

void UBlueprintExtenderFunctionLibrary::ImportFile(const FString& filePath)
{
	UMediaPlayer* _MediaPlayer = NewObject<UMediaPlayer>();

	if (!_MediaPlayer)
	{
		return;
	}
	_MediaPlayer->OpenFile(filePath);
}
