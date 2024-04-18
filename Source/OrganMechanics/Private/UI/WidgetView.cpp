// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetView.h"
#include "UI/Bridges/PropertyBridge.h"
#include "UI/DataModelInterface.h"

void UWidgetView::SetDataModel(UObject* _NewDataModel)
{
	DataModel = _NewDataModel;
	UpdateDataFromModel();
}

void UWidgetView::UpdateDataFromModel()
{
	check(DataModel);
	UPropertyBridge* data = IDataModelInterface::Execute_GetData(DataModel);
	ReceiveData(data);
	UControlBridge* controls = IDataModelInterface::Execute_GetControls(DataModel);
	ReceiveControls(controls);
}
