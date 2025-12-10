// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Abyss_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABYSSFPS_API UAbyss_AssetManager : public UAssetManager
{
	GENERATED_BODY()
	//------------------------------------------------------------------------------------------------------------------
public:
	static UAbyss_AssetManager& Get();
	virtual void StartInitialLoading() override;
	
};
