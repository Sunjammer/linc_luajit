#ifndef _LINC_LUA_H_
#define _LINC_LUA_H_


#include <hxcpp.h>

#include <sstream>
#include <iostream>

#include "../lib/lua/src/lua.hpp"


namespace linc {

    typedef ::cpp::Function < int(::cpp::Reference<lua_State>, ::String) > luaCallbackFN;
    // typedef ::cpp::Function < int(::cpp::Pointer<lua_State>, ::String) > luaCallbackFN;
    typedef ::cpp::Function < int(String) > HxTraceFN;

    namespace helpers {

        extern int luaDumpWriter(lua_State *L, const void* buffer, size_t size, void* data);
        extern const char* luaLoadReader(lua_State *L, void* data, size_t *size);
        extern int setErrorHandler(lua_State *L);
        extern void register_hxtrace_func(HxTraceFN fn);
        extern void register_hxtrace_lib(lua_State* L);
        extern ::Array<unsigned char> to_haxe_bytes(unsigned char* bytes, int length);

        struct BytesBox{
            public:
                ::Array_obj<unsigned char>* bytes;
                int offset;
        };

    }

    namespace lua {

        extern ::String version();
        extern ::String versionJIT();
        extern ::String tostring(lua_State *l, int v);
        extern ::String tolstring(lua_State *l, int v, size_t *len);
        extern ::String _typename(lua_State *l, int tp);

        extern int getstack(lua_State *L, int level, Dynamic ar);
        extern int getinfo(lua_State *L, const char *what, Dynamic ar);
        extern void dump(lua_State *l, Array<unsigned char> outbytes);
        extern int load(lua_State *l, Array<unsigned char> inbytes, ::String name);

    } // lua

    namespace lual {

        extern ::String checklstring(lua_State *l, int numArg, size_t *len);
        extern ::String optlstring(lua_State *L, int numArg, const char *def, size_t *l);
        extern ::String prepbuffer(luaL_Buffer *B);
        extern ::String gsub(lua_State *l, const char *s, const char *p, const char *r);
        extern ::String findtable(lua_State *L, int idx, const char *fname, int szhint);
        extern ::String checkstring(lua_State *L, int n);
        extern ::String optstring(lua_State *L, int n, const char *d);
        extern ::String ltypename(lua_State *L, int idx);

    }

    namespace callbacks {

        extern void set_callbacks_function(luaCallbackFN fn);
        extern void add_callback_function(lua_State *L, const char *name);
        extern void remove_callback_function(lua_State *L, const char *name);
        
    }


} //linc

#endif //_LINC_LUA_H_
