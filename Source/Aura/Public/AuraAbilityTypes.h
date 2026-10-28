//这个是给能力系统自定义类型用的  会写很多自定义类型
#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"
USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
public:
	
	
	bool IsCriticalHit()const { return bIsCriticalHit; }	
	bool IsBlockedHit()const { return bIsBlockedHit; }
	
	void SetIsCriticalHit(bool b) { bIsCriticalHit=b; }
	void SetIsBlockedHit(bool b) { bIsBlockedHit=b; }
	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FAuraGameplayEffectContext::StaticStruct();
	}
	
	/** Custom serialization, subclasses must override this */
	//对结构体里的每一个成员变量进行序列化
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
protected:
	
	UPROPERTY()
	//是否格挡
	bool bIsBlockedHit=false;
	
	UPROPERTY()
	//是否暴击
	bool bIsCriticalHit=false;
	
};
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext>:public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer=true,
		WithCopy=true,
	};
};
