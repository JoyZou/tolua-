
#include <stdio.h>
#include "lua4cpp.h"

void CLuaFn::Init()
{
    if( NULL == m_pState )
    {
        m_pState = luaL_newstate();
        luaL_openlibs( m_pState );
    }
}

void CLuaFn::Close()
{
    if ( NULL != m_pState )
    {
        lua_close( m_pState );
        m_pState = NULL;
    }
}

bool CLuaFn::LoadLuaFile( const char * filename_ )
{
    int nRet = 0;
    if ( NULL == m_pState )
    {
        printf( "[CLuaFn:: LoadLuaFile]m_pState is NULL.\n" );
        return false;
    }

    nRet = luaL_dofile( m_pState, filename_ );
    if (nRet != 0)
    {
        printf( "[CLuaFn:: LoadLuaFile]luaL_loadfile(%s) is file(%d)(%s).\n", filename_, nRet, lua_tostring(m_pState, -1) );
        return false;
    }

    return true;
}

int CLuaFn::CallLuaFn( const char * funname_, int param1_, int param2_ )
{
    int nRet = 0;
    if( NULL == m_pState )
    {
        printf( "[CLuaFn::CallFileFn]m_pState is NULL.\n" );
        return 0;
    }

    lua_getglobal( m_pState, funname_ );

    lua_pushnumber( m_pState, param1_ );
    lua_pushnumber( m_pState, param2_ );

    int nparam = lua_gettop( m_pState );
    printf( "[CLuaFn::CallFileFn]lua exec before stack has(%d) params count\n", nparam );

    nRet = lua_pcall( m_pState, 2, 1, 0 );
    if ( nRet != 0 )
    {
        printf( "[CLuaFn::CallFileFn]call function(%s) error(%d).\n", funname_, nRet );
        return 0;
    }

    int nSum = 0;
    if ( lua_isnumber(m_pState, -1) == 1 )
    {
        nSum = lua_tonumber( m_pState, -1 );
        printf( "[CLuaFn::CallFileFn]Sum = %d.\n", nSum );
    }

    nparam = lua_gettop( m_pState );
    printf( "[CLuaFn::CallFileFn]lua exec after stack has(%d) params count\n", nparam );

    lua_settop( m_pState, -2 );
    nparam = lua_gettop( m_pState );
    printf( "[CLuaFn::CallFileFn]lua clear stack has(%d) params count\n", nparam );


    return nSum;
}
