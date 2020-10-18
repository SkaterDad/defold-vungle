#pragma once

#include <dmsdk/sdk.h>

namespace dmVungleAds {

enum DefVungleCallbackType
{
  TYPE_IS_READY,
  TYPE_DID_START,
  TYPE_DID_ERROR,
  TYPE_DID_FINISH,
  TYPE_DID_REWARD,
  TYPE_INITIALIZED,
  TYPE_INIT_ERROR
};


struct DefVungleListener {
  DefVungleListener() : m_L(0), m_Callback(LUA_NOREF), m_Self(LUA_NOREF) {
  }
  lua_State* m_L;
  int m_Callback;
  int m_Self;
};

struct CallbackData
{
  int msg_type;
  char* key_1;
  char* value_1;
  char* key_2;
  char* value_2;
};

void SetLuaCallback(lua_State* L, int pos);
void CallbackUpdate();
void Initialize();
void Finalize();

void AddToQueue(int type, char*key_1, char*value_1, char*key_2, char*value_2);

} //namespace
