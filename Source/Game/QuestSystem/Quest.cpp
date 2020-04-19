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
/*----------------------------------------------------------------------------------------------------*/