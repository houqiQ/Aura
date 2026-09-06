// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/Data/CharaterClassInfo.h"

FCharacterClassDefaultInfo UCharaterClassInfo::GetCharacterClassInformation(ECharacterClass CharacterClass)
{
	return  CharacterClassInformation.FindChecked(CharacterClass);
}
