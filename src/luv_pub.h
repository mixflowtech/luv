#ifndef LUVPUB_H
#define LUVPUB_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "uv.h"

#if LUA_VERSION_NUM < 502
# define lua_rawlen lua_objlen
/* lua_...uservalue: Something very different, but it should get the job done */
# define lua_getuservalue lua_getfenv
# define lua_setuservalue lua_setfenv
# define luaL_newlib(L,l) (lua_newtable(L), luaL_register(L,NULL,l))
# define luaL_setfuncs(L,l,n) (assert(n==0), luaL_register(L,NULL,l))
# define lua_resume(L,F,n) lua_resume(L,n)
# define lua_pushglobaltable(L) lua_pushvalue(L, LUA_GLOBALSINDEX)
#endif

/* There is a 1-1 relation between a lua_State and a uv_loop_t
   These helpers will give you one if you have the other
   These are exposed for extensions built with luv
   This allows luv to be used in multithreaded applications.
*/
LUALIB_API lua_State* luv_state(uv_loop_t* loop);
/* All libuv callbacks will lua_call directly from this root-per-thread state
*/
LUALIB_API uv_loop_t* luv_loop(lua_State* L);

/* This is the main hook to load the library.
   This can be called multiple times in a process as long
   as you use a different lua_State and thread for each.
*/
LUALIB_API int luaopen_luv (lua_State *L);


#endif