// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Quest.h"
/*----------------------------------------------------------------------------------------------------*/
UQuest::UQuest()
{

}
/*----------------------------------------------------------------------------------------------------*/
FText UQuest::GetName() const
{
	return _name;
}
/*----------------------------------------------------------------------------------------------------*/
FText UQuest::GetDescription() const
{
	return _description;
}
/*----------------------------------------------------------------------------------------------------*/
float UQuest::GetDeadline() const
{
	return _deadline;
}
/*----------------------------------------------------------------------------------------------------*/
FObjectiveData UQuest::GetObjective() const
{
	return _objective;
}
//--------------------------------------------------------------------------------------------------
float UQuest::GetOzkazAddValue() const
{
	return _otkazAddValue;
}
//--------------------------------------------------------------------------------------------------
void UQuest::SetName(FText name)
{
	_name = name;
}
//--------------------------------------------------------------------------------------------------
void UQuest::SetDescription(FText description)
{
	_description = description;
}
//--------------------------------------------------------------------------------------------------
void UQuest::SetDeadline(float value)
{
	_deadline = value;
}
//--------------------------------------------------------------------------------------------------
void UQuest::SetObjective(FObjectiveData objectiveData)
{
	_objective = objectiveData;
}
//--------------------------------------------------------------------------------------------------
void UQuest::SetOtkazAddValue(float value)
{
	_otkazAddValue = value;
}
/*----------------------------------------------------------------------------------------------------*/