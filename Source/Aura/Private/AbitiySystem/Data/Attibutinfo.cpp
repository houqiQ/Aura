// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/Data/Attibutinfo.h"

FAuraAttributeInfo UAttibutinfo::FindAttributeInfo(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo Info:AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("没找到属性标签的Info  %s   FAuraAttributeInfo的名字 %s"),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
