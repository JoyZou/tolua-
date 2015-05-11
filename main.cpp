
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua4cpp.h"

#define ROOT "./script"

int main( int argc, char* argv[] )
{
    CLuaFn LuaFn;

    LuaFn.Init();
    LuaFn.LoadLuaFile( ROOT"/sample.lua" );
    int ret = LuaFn.CallLuaFn( "func_Add", 11, 12 );

    printf( "result : %d\n", ret );

    return 0;
}
