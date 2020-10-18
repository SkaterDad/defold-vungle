#define EXTENSION_NAME DefVungle
#define LIB_NAME "DefVungle"
#define MODULE_NAME "vungle"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)
#include "utils/LuaUtils.h"
#include "private_DefVungleCallback.h"
#include "private_DefVungle.h"

namespace dmVungleAds {
  
static int Initialize(lua_State* L) {
  const char *gameId_lua = luaL_checkstring(L, 1);
  SetLuaCallback(L, 2);
  initialize(gameId_lua);
  return 0;
}

static int SetCallback(lua_State* L) {
  SetLuaCallback(L, 1);
  return 0;
}

static int Load(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  load(placementId_lua);
  return 0;
}

static int Show(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  show(placementId_lua);
  return 0;
}

static int IsReady(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  bool status = isReady(placementId_lua);
  lua_pushboolean(L, status);
  return 1;
}

static int IsInitialized(lua_State* L) {
  bool status = isInitialized();
  lua_pushboolean(L, status);
  return 1;
}

static const luaL_reg Module_methods[] =
{
  {"initialize", Initialize},
  {"show", Show},
  {"load", Load},
  {"isReady", IsReady},
  {"isInitialized", IsInitialized},
  {"setCallback", SetCallback},
  {0, 0}
};

static void LuaInit(lua_State* L)
{
  int top = lua_gettop(L);
  luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
  lua_pushnumber(L, (lua_Number) name); \
  lua_setfield(L, -2, #name); \

  SETCONSTANT(TYPE_IS_READY)
  SETCONSTANT(TYPE_DID_START)
  SETCONSTANT(TYPE_DID_ERROR)
  SETCONSTANT(TYPE_DID_FINISH)
  SETCONSTANT(TYPE_DID_REWARD)
  SETCONSTANT(TYPE_INITIALIZED)
  SETCONSTANT(TYPE_INIT_ERROR)

#undef SETCONSTANT
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}

}//namespace

dmExtension::Result AppInitializeVungleAds(dmExtension::AppParams* params)
{
  return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeVungleAds(dmExtension::Params* params)
{
  dmVungleAds::LuaInit(params->m_L);
  dmVungleAds::InitExtension();
  dmVungleAds::Initialize();
  return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeVungleAds(dmExtension::AppParams* params)
{
  dmVungleAds::FinalizeExtension();
  return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeVungleAds(dmExtension::Params* params)
{
  dmVungleAds::Finalize();
  return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateVungleAds(dmExtension::Params* params)
{
  dmVungleAds::CallbackUpdate();
  return dmExtension::RESULT_OK;
}

#else // unsupported platforms

static dmExtension::Result AppInitializeVungleAds(dmExtension::AppParams* params)
{
  return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeVungleAds(dmExtension::Params* params)
{
  return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeVungleAds(dmExtension::AppParams* params)
{
  return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeVungleAds(dmExtension::Params* params)
{
  return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateVungleAds(dmExtension::Params* params)
{
  return dmExtension::RESULT_OK;
}

#endif // platforms


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeVungleAds, AppFinalizeVungleAds, InitializeVungleAds, UpdateVungleAds, 0, FinalizeVungleAds)
