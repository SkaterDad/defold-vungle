#pragma once
#if defined(DM_PLATFORM_ANDROID)

namespace dmVungleAds {

void InitExtension();
void FinalizeExtension();

void initialize(const char*game_id);
void load(char* placementId);
void show(char* placementId);

bool isReady(char* placementId);
bool isInitialized();

} //namespace

#endif
