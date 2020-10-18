#pragma once
#if defined(DM_PLATFORM_ANDROID)

namespace dmVungleAds {

void InitExtension();
void FinalizeExtension();

void initialize(const char*game_id, bool is_debug);
void load(char* placementId);
void show(char* placementId);

bool isReady(char* placementId);
bool isInitialized();

} //namespace

#endif
