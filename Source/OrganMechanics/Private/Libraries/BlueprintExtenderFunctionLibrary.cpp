// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/BlueprintExtenderFunctionLibrary.h"

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
