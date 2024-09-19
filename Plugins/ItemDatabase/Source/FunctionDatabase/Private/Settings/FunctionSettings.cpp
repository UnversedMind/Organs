// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/FunctionSettings.h"
#include "Functions/FunctionInfo.h"

TArray<FName> UFunctionSettings::GetFunctionIdentifiers()
{
	UFunctionSettings* functionSettings = const_cast<UFunctionSettings*>(GetDefault<UFunctionSettings>());
	UDataTable* dataTable = const_cast<UDataTable*>(functionSettings->GetFunctionDataTable());

	if (!dataTable) 
	{
		return TArray<FName>();
	}

	return dataTable->GetRowNames();
}

FFunctionInfo UFunctionSettings::GetFunctionInfoFromIdentifier(FName _FunctionIdentifier) 
{
	UFunctionSettings* functionSettings = const_cast<UFunctionSettings*>(GetDefault<UFunctionSettings>());
	UDataTable* dataTable = const_cast<UDataTable*>(functionSettings->GetFunctionDataTable());

	if (!dataTable)
	{
		return FFunctionInfo();
	}

	if (!dataTable->GetRowNames().Contains(_FunctionIdentifier))
	{
		return FFunctionInfo();
	}
	FFunctionInfo functionInfo = FFunctionInfo();
	functionInfo = *dataTable->FindRow<FFunctionInfo>(_FunctionIdentifier, FString());
	return functionInfo;
}

TArray<FFunctionInfo> UFunctionSettings::GetFunctionInfoFromIdentifiers(TArray<FName> _FunctionIdentifiers)
{
	UFunctionSettings* functionSettings = const_cast<UFunctionSettings*>(GetDefault<UFunctionSettings>());
	UDataTable* dataTable = const_cast<UDataTable*>(functionSettings->GetFunctionDataTable());

	if (!dataTable)
	{
		return TArray<FFunctionInfo>();
	}

	TArray<FFunctionInfo> functionInfoArray;
	for (FName functionIdentifier : _FunctionIdentifiers) 
	{
		if (!dataTable->GetRowNames().Contains(functionIdentifier))
		{
			continue;
		}
		FFunctionInfo functionInfo = *dataTable->FindRow<FFunctionInfo>(functionIdentifier, FString());
		functionInfoArray.Add(functionInfo);
	}
	return functionInfoArray;
}

UFunctionSettings::UFunctionSettings()
{
	LoadFunctionDataTable();
}

void UFunctionSettings::LoadFunctionDataTable()
{
	FunctionListInstance = FunctionList.LoadSynchronous();
}

const UDataTable* UFunctionSettings::GetFunctionDataTable()
{
	if (!FunctionListInstance)
	{
		LoadFunctionDataTable();
	}
	return FunctionListInstance;
}
