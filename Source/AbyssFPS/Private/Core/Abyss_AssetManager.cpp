// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "Core/Abyss_AssetManager.h"

#include "Tags/AbyssGameplayTags.h"

UAbyss_AssetManager& UAbyss_AssetManager::Get()
{
	UAbyss_AssetManager* This = Cast<UAbyss_AssetManager>(GEngine->AssetManager);
	checkf(This, TEXT("Invalid AssetManagerClass set in DefaultEngine.ini. It must be set to Abyss_AssetManager!"));
	if (This)
	{
		return *This;
	}
	else
	{
		return *NewObject<UAbyss_AssetManager>();
	}
	
}

void UAbyss_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
