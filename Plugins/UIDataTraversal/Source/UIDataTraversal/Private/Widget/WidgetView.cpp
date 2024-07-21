// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetView.h"
#include "Bridges/PropertyBridges/PropertyBridge.h"
#include "Interfaces/DataModelInterface.h"

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
